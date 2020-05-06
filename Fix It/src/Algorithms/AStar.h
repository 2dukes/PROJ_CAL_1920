//
// Created by Rui Pinto on 5/6/2020.
//

#ifndef FIX_IT_ASTAR_H
#define FIX_IT_ASTAR_H

#include "../Graph/Graph.h"
#include <math.h>

template <class T>
class AStar { // TODO TEST A* ALGORITHM USING CLASSES TESTS! -> SHOULD GIVE AND APROXIMATE/SAME RESULT!
protected:
    Graph<T>* graph;

public:
    AStar(const Graph<T>* graph);

    void AStarShortestPath(const T &origin, const T &dest);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t);
    double heuristicDistance(Vertex<T>* origin, Vertex<T>* dest);
    double degreesToRadians(double degrees);

    friend class Graph<T>;
};

template<class T>
AStar<T>::AStar(const Graph<T> *graph) {
    this->graph = graph;
}

template<class T>
double AStar<T>::degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

template<class T>
double AStar<T>::heuristicDistance(Vertex<T> *origin, Vertex<T> *dest) {
    double earthRadiusKm = 6371.0;

    double dLat = degreesToRadians(dest->latitude - origin->latitude);
    double dLon = degreesToRadians(dest->longitude - origin->longitude);

    double tempLat1 = degreesToRadians(origin->latitude);
    double tempLat2 = degreesToRadians(dest->latitude);

    double a = sin(dLat/2) * sin(dLat/2) +
            sin(dLon/2) * sin(dLon/2) * cos(tempLat1) * cos(tempLat2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return earthRadiusKm * c;
}

template<class T>
inline bool AStar<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t) {
    if (v->dist + weight < w->dist) {
        w->dist = v->dist + weight;
        w->gScore = w->dist +  heuristicDistance(v, t);
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
    s->gScore = heuristicDistance(s, t);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while(!q.empty()) {
        auto v = q.extractMin();

        if(v->getInfo() == t)
            break;

        for(auto e : v->adj) {
            auto oldDist = e.dest->dist;
            if (relax(v, e.dest, e.weight, t)) {
                if (oldDist == INF)
                    q.insert(e.dest);
                else
                    q.decreaseKey(e.dest);
            }
        }
    }
}

#endif //FIX_IT_ASTAR_H
