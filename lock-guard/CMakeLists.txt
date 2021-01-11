cmake_minimum_required(VERSION 3.17)
project(lock_guard)

set(CMAKE_CXX_STANDARD 14)

add_executable(lock_guard main.cpp)

target_link_libraries(lock_guard pthread)