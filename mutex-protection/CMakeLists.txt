cmake_minimum_required (VERSION 3.16)

project(concurrency)

find_package (Threads)
add_executable (concurrency main.cpp)



TARGET_LINK_LIBRARIES(concurrency ${CMAKE_THREAD_LIBS_INIT})
