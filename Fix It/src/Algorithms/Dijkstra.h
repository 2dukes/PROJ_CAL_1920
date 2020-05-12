#ifndef FIX_IT_DIJKSTRA_H
#define FIX_IT_DIJKSTRA_H

#include <chrono>
#include "../Graph/Graph.h"

template <class T>
class Dijkstra {
protected:
    Graph<T>* graph;

public:
    Dijkstra(const Graph<T>* graph);

    void dijkstraShortestPath(const T &origin, const T &dest, bool isInverted);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight, bool isInverted);

    friend class Graph<T>;
};

template<class T>
Dijkstra<T>::Dijkstra(const Graph<T> *graph) {
    this->graph = graph;
}

template<class T>
inline bool Dijkstra<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight, bool isInverted) {
    if (v->weight + weight < w->weight) {
        w->weight = v->weight + weight;
        w->path = v;
        w->visited = true;
        return true;
    }
    else
        return false;
}

template<class T>
void Dijkstra<T>::dijkstraShortestPath(const T &origin, const T &dest, bool isInverted) {
    auto t = findVertex(dest); // Destination Vertex
    auto s = graph->initPathAlg(origin);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while(!q.empty()) {
        auto v = q.extractMin();

        if(v->getInfo() == t)
            break;
//
//        if (isInverted) {
//            v = findVertex(v->getInfo()); // do this only if its inverted graph
//        }
//
//        this->visited[v->info.getId()] = true;

        for(auto e : v->adj) {
            auto oldDist = e.dest->dist;
            if (relax(v, e.dest, e.weight)) {
                if (oldDist == INF)
                    q.insert(e.dest);
                else
                    q.decreaseKey(e.dest);
            }
        }
    }
}

#endif //FIX_IT_DIJKSTRA_H
