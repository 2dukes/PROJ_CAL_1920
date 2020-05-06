cmake_minimum_required(VERSION 3.15)
project(Fix_It)

set(CMAKE_CXX_STANDARD 14)
include_directories(src)
add_executable(Fix_It main.cpp src/Picket.h src/Picket.cpp src/Task.h src/Task.cpp src/Utils/Time.h src/Utils/Time.cpp)