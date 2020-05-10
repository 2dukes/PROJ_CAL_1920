cmake_minimum_required(VERSION 3.15)
project(Fix_It)

set(CMAKE_CXX_STANDARD 14)

add_executable(Fix_It main.cpp src/Graph/Graph.h
                src/Graph/TaskEdge.h
                src/Graph/MutablePriorityQueue.h
                src/Algorithms/SearchAlgorithms.h
                src/Algorithms/Dijkstra.h
                src/Algorithms/AStar.h)