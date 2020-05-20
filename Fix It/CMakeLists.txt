cmake_minimum_required(VERSION 3.15)
project(Fix_It)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32 wsock32)

include_directories(src)
add_executable( Fix_It
                main.cpp
                src/Graph/Graph.h
                src/Graph/TaskEdge.h
                src/Graph/MutablePriorityQueue.h
                src/Algorithms/SearchAlgorithms.h
                src/Algorithms/Dijkstra.h
                src/Algorithms/AStar.h
                src/Algorithms/DijkstraBiDir.h
                src/Picket.h
                src/Picket.cpp
                src/Task.h
                src/Task.cpp
                src/Utils/Time.h
                src/Utils/Time.cpp
                src/Company.h
                src/Company.cpp
                src/Utils/NecessaryFunctions_NameSpaces.h
                src/Utils/NecessaryFunctions_NameSpaces.cpp
                src/UserInterface/Menu.cpp
                src/UserInterface/Menu.h
                src/Algorithms/AStarBiDir.h
                src/GraphInterface.cpp
                lib/graphviewer.cpp
                lib/edgetype.h
                lib/connection.cpp
                src/Algorithms/TSP.h
                src/Algorithms/Clustering.h
                src/Algorithms/Pairing.h
        )
