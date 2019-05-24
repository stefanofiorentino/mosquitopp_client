cmake_minimum_required(VERSION 3.10)
project(mosquittopp_client)

set(CMAKE_CXX_STANDARD 14)

link_directories(/usr/local/lib)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -DDEBUG)

add_subdirectory(lib)
add_subdirectory(src)
