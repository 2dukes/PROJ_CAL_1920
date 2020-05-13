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

    Vertex<T>* dijkstraShortestPathBi(const T &origin, const T &dest, bool isInverted);
    void dijkstraShortestPath(const T &origin, const T &dest);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
    bool relaxInv(Vertex<T> *v, Vertex<T> *w, double weight);

    bool isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex);
    void invDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v) const;
    void directDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v) const;

    friend class Graph<T>;
};

template<class T>
Dijkstra<T>::Dijkstra(const Graph<T> *graph) {
    this->graph = graph;
}

template<class T>
inline bool Dijkstra<T>::relaxInv(Vertex<T> *v, Vertex<T> *w, double weight) {
    if (v->weight + weight < w->weight) {
        w->weight = v->weight + weight;
        v->path = w; // Careful... Path Goes
        w->invVisited = true;
        return true;
    }
    return false;
}
template<class T>
inline bool Dijkstra<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
    if(v->weight + weight < w->weight) {
        w->weight = v->weight + weight;
        w->path = v;
        w->visited = true;
        return true;
    }
    return false;
}

template <class T>
void Dijkstra<T>::dijkstraShortestPath(const T &origin, const T &dest) {
    auto t = findVertex(dest); // Destination Vertex
    auto s = graph->initPathAlg(origin);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while(!q.empty()) {
        auto v = q.extractMin();

        if(v->getInfo() == t->getInfo())
            break;

        directDijkstraStep(q, v);
    }
}

template <class T>
bool Dijkstra<T>::isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex) {
    if(vertex->invVisited && vertex->visited) {
        if(!isInverted)
            vertex->path = previousVertex;
        else
            previousVertex->path = vertex;
        return true;
    }
    return false;
}

template <class T> // Returns Intersecting Vertex
Vertex<T>* Dijkstra<T>::dijkstraShortestPathBi(const T &origin, const T &dest, bool isInverted) {
    auto s = findVertex(origin);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);

    Vertex<T>* prevVertex = nullptr;
    while(!q.empty()) {
        auto v = q.extractMin();

        if(isIntersecting(v, isInverted, prevVertex))
            return v;

        if (isInverted)
            invDijkstraStep(q, v);
        else
            directDijkstraStep(q, v);
        prevVertex = v;
    }
}

template<class T>
void Dijkstra<T>::directDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v) const {
    for(auto e : v->outgoing) {
        auto oldDist = e->dest->dist;
        if (relax(v, e->dest, e.weight)) {
            if (oldDist == INF)
                q.insert(e->dest);
            else
                q.decreaseKey(e->dest);
        }
    }
}

template<class T>
void Dijkstra<T>::invDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v) const {
    for(auto e : v->incoming) {
        auto oldDist = e->orig->dist;
        if (relaxInv(v, e->orig, e.weight)) {
            if (oldDist == INF)
                q.insert(e->orig);
            else
                q.decreaseKey(e->orig);
        }
    }
}

#endif //FIX_IT_DIJKSTRA_H
