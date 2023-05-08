#include "property_generated.h"
#include "flatbuffers/reflection.h"
#include "flatbuffers/util.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fstream>
#include <iterator>
#include <unistd.h>
#include <cstring>

/**
 * The example property tree:
 *
 *          root
 *        /   |    \
 *   child1 child2 child3
 *
 */
void BuildProperty(flatbuffers::FlatBufferBuilder &builder)
{
    std::vector<flatbuffers::Offset<Property>> sub_properties_vector;

    for (int i = 1; i <= 3; i++)
    {
        auto property_name = builder.CreateString("child" + std::to_string(i));
        auto property_value = builder.CreateString(std::to_string(i));
        auto property_type = builder.CreateString("int");
        auto property_sub_properties = builder.CreateVector(std::vector<flatbuffers::Offset<Property>>());

        sub_properties_vector.emplace_back(CreateProperty(
            builder, property_name, property_value, property_type, property_sub_properties));
    }

    auto property_name = builder.CreateString("root");
    auto property_value = builder.CreateString("0");
    auto property_type = builder.CreateString("int");
    auto property_sub_properties = builder.CreateVector(sub_properties_vector);
    auto root_property = CreateProperty(
        builder, property_name, property_value, property_type, property_sub_properties);

    builder.Finish(root_property);
}

void UpdateProperty(Property *property)
{
    auto updated_name = const_cast<char *>(property->mutable_name()->c_str());

    // The length of updated string should not exceed the length of the original string
    std::string updated_name_str = "foo";
    assert(updated_name_str.length() <= strlen(updated_name));
    strcpy(updated_name, updated_name_str.c_str());
}

int main(int /*argc*/, const char * /*argv*/[])
{
    flatbuffers::FlatBufferBuilder builder;
    BuildProperty(builder);
    auto property = GetProperty(builder.GetBufferPointer());
    UpdateProperty(const_cast<Property *>(property));

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

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        std::cerr << "Failed to connect to receiver: " << strerror(errno) << std::endl;
        return -1;
    }

    int data_size = builder.GetSize();

    if (send(sockfd, &data_size, sizeof(data_size), 0) == -1)
    {
        std::cerr << "Failed to send data size: " << strerror(errno) << std::endl;
        return -1;
    }

    if (send(sockfd, builder.GetBufferPointer(), data_size, 0) == -1)
    {
        std::cerr << "Failed to send data: " << strerror(errno) << std::endl;
        return -1;
    }

    return 0;
}