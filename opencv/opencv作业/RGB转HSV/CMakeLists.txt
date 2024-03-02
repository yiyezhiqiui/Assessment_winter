cmake_minimum_required(VERSION 3.2)
project(picture)

find_package(OpenCV)
add_executable(test main.cpp)
target_link_libraries(test ${OpenCV_LIBS})