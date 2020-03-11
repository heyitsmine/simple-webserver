cmake_minimum_required(VERSION 3.13)
project(simple-webserver C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(tiny tiny-plain.c csapp.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/cgi-bin)
add_executable(adder cgi-bin/adder.c)
add_executable(form-adder cgi-bin/form-adder.c)
add_executable(post-adder cgi-bin/post-adder.c)

target_link_libraries(tiny pthread)
