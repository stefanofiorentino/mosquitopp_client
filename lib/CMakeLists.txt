set(CMAKE_CXX_STANDARD 11)

add_library(mosquittoppWrapperLib
        mqtt.cpp
        include/mqtt.h)

target_link_libraries(mosquittoppWrapperLib
        mosquittopp
        -pthread)

add_library(mosquittoppWrapper SHARED
        mqtt.cpp
        include/mqtt.h)

target_link_libraries(mosquittoppWrapper
        mosquittopp
        -pthread)