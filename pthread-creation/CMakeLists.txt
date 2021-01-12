cmake_minimum_required(VERSION 3.16)
project(pthread_creattion C)

set(CMAKE_C_STANDARD 99)

add_executable(pthread_creattion main.c)

TARGET_LINK_LIBRARIES(pthread_creattion pthread)