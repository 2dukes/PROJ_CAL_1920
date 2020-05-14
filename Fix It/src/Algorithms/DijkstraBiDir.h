#ifndef FIX_IT_DIJKSTRABIDIR_H
#define FIX_IT_DIJKSTRABIDIR_H

#include "Dijkstra.h"

template <class T>
class DijkstraBiDir: public Dijkstra<T> { // TODO TEST Bidirectional Dijkstra!
public:
    DijkstraBiDir(const Graph<T>* graph);
    void dijkstraBiDirShortestPath(const T &origin, const T &dest);
};

template <class T>
DijkstraBiDir<T>::DijkstraBiDir(const Graph<T>* graph) : Dijkstra<T>(graph) { }

template <class T>
void DijkstraBiDir<T>::dijkstraBiDirShortestPath(const T &origin, const T &dest) {
    this->graph->initPathAlg(origin);
    this->graph->initDestinationPathAlg(dest); // Destination weight is also zero!
    this->hasIntersected = false;

//    auto start = chrono::steady_clock::now();

    auto f1 = thread([this, origin, dest] {
        this->dijkstraShortestPathBi(origin, dest, false);
    });

    this->dijkstraShortestPathBi(dest, origin, true);
    f1.join(); // Wait...

//    auto end = chrono::steady_clock::now();
//    double time_elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

#endif //FIX_IT_DIJKSTRABIDIR_H
