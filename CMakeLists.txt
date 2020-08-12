cmake_minimum_required(VERSION 3.13)
project(simple-webserver C)

set(CMAKE_C_STANDARD 99)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(tiny-plain tiny-plain.c csapp.c)
add_executable(tiny-proc tiny-proc.c csapp.c)
add_executable(tiny-thread tiny-thread.c csapp.c)
add_executable(tiny-select tiny-select-src/main.c tiny-select-src/tiny.c tiny-select-src/pool.c csapp.c)
add_executable(tiny-poll tiny-poll-src/main.c tiny-poll-src/tiny.c tiny-poll-src/pool.c csapp.c)
add_executable(tiny-epoll tiny-epoll-src/main.c tiny-epoll-src/tiny.c tiny-epoll-src/pool.c csapp.c)
add_executable(tiny-threadpool tiny-threadpool-src/sbuf.c tiny-threadpool-src/main.c tiny-threadpool-src/tiny.c csapp.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/cgi-bin)
add_executable(adder cgi-bin/adder.c)
add_executable(form-adder cgi-bin/form-adder.c)
add_executable(post-adder cgi-bin/post-adder.c)

target_link_libraries(tiny-plain pthread)
target_link_libraries(tiny-proc pthread)
target_link_libraries(tiny-thread pthread)
target_link_libraries(tiny-select pthread)
target_link_libraries(tiny-poll pthread)
target_link_libraries(tiny-epoll pthread)
target_link_libraries(tiny-threadpool pthread)
