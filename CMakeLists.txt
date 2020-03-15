cmake_minimum_required(VERSION 3.13)
project(simple-webserver C)

set(CMAKE_C_STANDARD 99)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(tiny-plain tiny-plain.c csapp.c)
add_executable(tiny-proc tiny-proc.c csapp.c)
add_executable(tiny-select tiny-select-src/main.c tiny-select-src/tiny.c tiny-select-src/pool.c csapp.c)
add_executable(tiny-thread tiny-thread-src/sbuf.c tiny-thread-src/main.c tiny-thread-src/tiny.c csapp.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/cgi-bin)
add_executable(adder cgi-bin/adder.c)
add_executable(form-adder cgi-bin/form-adder.c)
add_executable(post-adder cgi-bin/post-adder.c)

target_link_libraries(tiny-plain pthread)
target_link_libraries(tiny-proc pthread)
target_link_libraries(tiny-select pthread)
target_link_libraries(tiny-thread pthread)
