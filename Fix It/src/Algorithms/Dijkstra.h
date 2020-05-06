#ifndef FIX_IT_DIJKSTRA_H
#define FIX_IT_DIJKSTRA_H

#include "../Graph/Graph.h"

template <class T>
class Dijkstra {
protected:
    Graph<T>* graph;

public:
    Dijkstra(const Graph<T>* graph);

    Vertex<T>* initPathAlg(const T &origin);
    void dijkstraShortestPath(const T &origin);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight);

    friend class Graph<T>;
};

template<class T>
Dijkstra<T>::Dijkstra(const Graph<T> *graph) {
    this->graph = graph;
}

template<class T>
Vertex<T> * Dijkstra<T>::initPathAlg(const T &origin) {
    for(auto v : graph->vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    auto s = graph->findVertex(origin);
    s->dist = 0;
    return s;
}

template<class T>
inline bool Dijkstra<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
    if (v->dist + weight < w->dist) {
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    else
        return false;
}

template<class T>
void Dijkstra<T>::dijkstraShortestPath(const T &origin) {
    auto s = initPathAlg(origin);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while(!q.empty()) {
        auto v = q.extractMin();
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
