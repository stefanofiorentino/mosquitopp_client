cmake_minimum_required(VERSION 3.10)
project(mosquittopp_client)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

link_directories(/usr/local/lib)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -DDEBUG)

add_library(mosquittoppWrapperLib
        mqtt.cpp
        include/mqtt.h)

target_link_libraries(mosquittoppWrapperLib
        mosquitto
        mosquittopp)

add_executable(mosquittopp_client
        main.cpp)

target_link_libraries(mosquittopp_client
        mosquittoppWrapperLib)
