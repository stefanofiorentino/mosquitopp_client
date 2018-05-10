
set(CMAKE_CXX_STANDARD 11)

link_directories(/usr/local/lib)

add_executable(publishAndWaitForResponseWithTimeout
        main.cpp)

target_link_libraries(publishAndWaitForResponseWithTimeout
        mosquittoppWrapperLib)
