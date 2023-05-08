#include "flatbuffers/reflection.h"
#include "flatbuffers/util.h"
#include <iostream>
#include <format>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fstream>
#include <iterator>
#include <unistd.h>
#include <cstring>

void VisitTable(const flatbuffers::Table *table, const reflection::Schema *schema);

void VisitVec(const flatbuffers::VectorOfAny *vec, const reflection::Field *field, const reflection::Schema *schema)
{
    std::cout << "[" << std::endl;
    auto element_base_type = field->type()->element();
    auto elemobjectdef = element_base_type == reflection::Obj
                             ? schema->objects()->Get(field->type()->index())
                             : nullptr;
    switch (element_base_type)
    {
    case reflection::Obj:
    {
        if (!elemobjectdef->is_struct())
        {
            // This is a vector of tables.
            for (int i = 0; i < vec->size(); i++)
            {
                flatbuffers::Table *tableelem =
                    flatbuffers::GetAnyVectorElemPointer<flatbuffers::Table>(vec, i);
                VisitTable(tableelem, schema);
            }
        }
        else
        {
            std::cerr << "Not implemented" << std::endl;
        }
        break;
    }

    default:
    {
        std::cerr << "Not implemented" << std::endl;
        break;
    }
    }
    std::cout << "]" << std::endl;
}

void VisitTable(const flatbuffers::Table *table, const reflection::Schema *schema)
{
    std::cout << "{" << std::endl;
    auto root_table = schema->root_table();
    auto fields = root_table->fields();
    for (int i = 0; i < fields->size(); i++)
    {
        auto field = fields->Get(i);
        std::cout << field->name()->c_str() << ": ";
        switch (field->type()->base_type())
        {
        case reflection::String:
        {
            auto str = flatbuffers::GetFieldS(*table, *field);
            std::cout << str->c_str() << std::endl;
            break;
        }
        case reflection::Vector:
        {
            auto vec = flatbuffers::GetFieldAnyV(*table, *field);
            VisitVec(vec, field, schema);
            break;
        }
        default:
        {
            std::cerr << "Not implemented" << std::endl;
            break;
        }
        }
    }
    std::cout << "}" << std::endl;
}

int main(int /*argc*/, const char * /*argv*/[])
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        return -1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Failed to bind: " << strerror(errno) << std::endl;
        return -1;
    }

    if (listen(sockfd, 3) < 0)
    {
        std::cerr << "Error while listening: " << strerror(errno) << std::endl;
        return -1;
    }

    int new_sockfd = accept(sockfd, (struct sockaddr *)&serv_addr, (socklen_t *)&serv_addr);
    if (new_sockfd < 0)
    {
        std::cerr << "Can't accept: " << strerror(errno) << std::endl;
        return -1;
    }

    int data_size = 0;
    if (recv(new_sockfd, &data_size, sizeof(data_size), 0) == -1)
    {
        std::cerr << "Failed to receive data size: " << strerror(errno) << std::endl;
        close(new_sockfd);
        close(sockfd);
        return -1;
    }

    char *buffer = new char[data_size + 1];
    if (recv(new_sockfd, buffer, data_size, 0) == -1)
    {
        std::cerr << "Failed to receive data: " << strerror(errno) << std::endl;
        close(new_sockfd);
        close(sockfd);
        return -1;
    }

    std::ifstream input("../data/property.bfbs", std::ios::binary);
    std::string bfbsfile(std::istreambuf_iterator<char>(input), {});
    auto schema = reflection::GetSchema(bfbsfile.c_str());

    auto root = flatbuffers::GetAnyRoot((uint8_t *)buffer);

    VisitTable(root, schema);

    return 0;
}