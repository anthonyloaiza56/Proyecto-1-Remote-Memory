cmake_minimum_required(VERSION 3.8)
project(server2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(server2 ${SOURCE_FILES})
set(THREADS PREFER PTHREAD FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(server2 Threads::Threads)