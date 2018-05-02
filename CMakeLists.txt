cmake_minimum_required(VERSION 3.9.6)
project(UE2_avltree)

set(CMAKE_CXX_STANDARD 17)

add_executable(UE2_avltree main.cpp Tree.h Node.h)

add_executable(test_generator test_generator/main.cpp)