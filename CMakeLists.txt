cmake_minimum_required(VERSION 3.20)
project(ultra)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(ultra main.cpp)

target_link_libraries(ultra ${OpenCV_LIBS})