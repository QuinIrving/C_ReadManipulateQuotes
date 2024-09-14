cmake_minimum_required(VERSION 3.21)
project(Assignment2 C)

set(CMAKE_C_STANDARD 11)
configure_file(${CMAKE_SOURCE_DIR}/quotes.txt ${CMAKE_BINARY_DIR}/quotes.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/output.txt ${CMAKE_BINARY_DIR}/output.txt COPYONLY)

add_executable(Assignment2 main.c)
