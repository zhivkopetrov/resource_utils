cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(resource_utils CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example resource_utils::resource_utils)
