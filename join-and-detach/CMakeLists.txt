cmake_minimum_required(VERSION 3.17)
project(joint_and_detach)

set(CMAKE_CXX_STANDARD 14)

add_executable(joint_and_detach main.cpp)

target_link_libraries(joint_and_detach pthread)