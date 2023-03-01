cmake_minimum_required(VERSION 3.24)
project(lab_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_3 main.cpp)

target_include_directories(lab_3 PRIVATE ${CMAKE_SOURCE_DIR} )