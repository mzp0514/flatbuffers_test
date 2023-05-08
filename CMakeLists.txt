# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_flatbuffers)


# Add an executable
add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(sender
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(receiver
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

set_property(TARGET sender PROPERTY CXX_STANDARD 20)
set_property(TARGET sender PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET  receiver PROPERTY CXX_STANDARD 20)
set_property(TARGET  receiver PROPERTY CXX_STANDARD_REQUIRED ON)
