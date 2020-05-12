//
// Created by Rui Pinto on 5/6/2020.
//

#ifndef FIX_IT_ASTAR_H
#define FIX_IT_ASTAR_H

#include "../Graph/Graph.h"
#include <math.h>

template <class T>
class AStar { // TODO TEST A* ALGORITHM USING CLASSES TESTS! -> SHOULD GIVE AND APROXIMATE/SAME RESULT! Probably Vertex<T> will be substituted by AVertex! Or make a cast...
protected:
    Graph<T>* graph;

public:
    AStar(const Graph<T>* graph);

    void AStarShortestPath(const T &origin, const T &dest);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t);
    double heuristicDistance(Vertex<T>* origin, Vertex<T>* dest);

    friend class Graph<T>;
};

template<class T>
AStar<T>::AStar(const Graph<T> *graph) {
    this->graph = graph;
}

template<class T>
double AStar<T>::heuristicDistance(Vertex<T> *origin, Vertex<T> *dest) {
    return sqrt(pow(origin->x - dest->x, 2) + pow(origin->y - dest->y, 2));

}

template<class T>
inline bool AStar<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t) {
    if (v->weight + weight + heuristicDistance(w, t) < w->weight) {
        w->dist = v->weight + weight;
        w->weight = v->weight + weight + heuristicDistance(w, t);
        w->path = v;
        return true;
    }
    else
        return false;
}

template<class T>
void AStar<T>::AStarShortestPath(const T &origin, const T &dest) {
    auto t = findVertex(dest); // Destination Vertex
    auto s = graph->initPathAlg(origin);

    MutablePriorityQueue<Vertex<T>> q; // Ordered by gScore
    q.insert(s);
    while(!q.empty()) {
        auto v = q.extractMin();
        v->visited = true;

        if(v->getInfo() == t->getInfo())
            break;

//        if (isInverted) {
//            origin = findVertex(origin->getInfo()); // do this only if its inverted graph
//        }
//
//        this->visited[origin->info.getId()] = true;

        for(auto e : v->outgoing) {
            if (relax(v, e.dest, e.weight, t)) {
                if (!q.find(v))
                    q.insert(e.dest);
                else
                    q.decreaseKey(e.dest);
            }
        }
    }
}

#endif //FIX_IT_ASTAR_H
