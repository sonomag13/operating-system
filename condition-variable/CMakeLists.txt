cmake_minimum_required(VERSION 3.17)

project(condition-variable)

find_package(Threads REQUIRED)

add_executable(condition-variable main.cpp)

target_link_libraries(condition-variable PRIVATE Threads::Threads)

