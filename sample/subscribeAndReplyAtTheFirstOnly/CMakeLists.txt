
set(CMAKE_CXX_STANDARD 11)

link_directories(/usr/local/lib)

add_executable(subscribeAndReplyAtTheFirstOnly
        main.cpp)

target_link_libraries(subscribeAndReplyAtTheFirstOnly
        mosquittoppWrapperLib)
