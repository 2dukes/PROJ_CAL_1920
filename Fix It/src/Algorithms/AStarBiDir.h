#ifndef FIX_IT_ASTARBIDIRECTIONAL_H
#define FIX_IT_ASTARBIDIRECTIONAL_H

#include "../Graph/Graph.h"
#include "AStar.h"

template <class T>
class AStarBiDir : public AStar<T> {
    AStarBiDir(const Graph<T>* graph);
    void AStarBiDirShortestPath(const T &origin, const T &dest);
};

template <class T>
AStarBiDir<T>::AStarBiDir(const Graph<T>* graph) : AStar<T>(graph) { }

template <class T>
void AStarBiDir<T>::AStarBiDirShortestPath(const T &origin, const T &dest) {
    this->graph->initPathAlg(origin);
    this->graph->initDestinationPathAlg(origin); // Destination weight is also zero!

//    auto start = chrono::steady_clock::now();

    auto f1 = thread([this, origin, dest] {
        this->AStarShortestPathBi(origin, dest, true);
    });

    this->AStarShortestPathBi(dest, origin, false);
    f1.join(); // Wait...

//    auto end = chrono::steady_clock::now();
//    double time_elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

#endif //FIX_IT_ASTARBIDIRECTIONAL_H
