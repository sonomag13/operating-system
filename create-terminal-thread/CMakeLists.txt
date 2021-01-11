cmake_minimum_required(VERSION 3.17)

project(multithread)

add_executable(multithread main.cpp)

target_link_libraries(multithread pthread)