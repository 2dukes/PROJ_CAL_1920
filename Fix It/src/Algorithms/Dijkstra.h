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

    // ----------------------------- MULTI THREAD ----------------------------- //

    bool dijkstraShortestPathBi(const T &origin, const T &dest, bool isInverted);
    bool isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* previousVertex);
    bool relaxInv(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* previousVertex);
    void invDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, Vertex<T>* previousVertex) const;
    void directDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, Vertex<T>* previousVertex) const;

    // ----------------------------- SINGLE THREAD ----------------------------- //

    void dijkstraShortestPath(const T &origin, const T &dest);
    bool relaxSingle(Vertex<T> *v, Vertex<T> *w, double weight);
    void directDijkstraStepSingle(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v) const;

    bool hasIntersected;
    friend class Graph<T>;
};

template<class T>
Dijkstra<T>::Dijkstra(const Graph<T> *graph) {
    this->graph = graph;
}

// ----------------------------- MULTI THREAD ----------------------------- //

template<class T>
inline bool Dijkstra<T>::relaxInv(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* previousVertex) {
    if (v->weight + weight < w->weight && !hasIntersected) {
        if(isIntersecting(v, true, previousVertex))
            return false;
        else {
            w->weight = v->weight + weight;
            v->path = w; // Careful... Path Goes
            w->invVisited = true;
            return true;
        }
    }
    return false;
}
template<class T>
inline bool Dijkstra<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* previousVertex) {
    if(v->weight + weight < w->weight && !hasIntersected) {
        if(isIntersecting(v, false, previousVertex))
            return false;
        else {
            w->weight = v->weight + weight;
            w->path = v;
            w->visited = true;
            return true;
        }
    }
    return false;
}

template <class T>
bool Dijkstra<T>::isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex) {
        if(!isInverted && vertex->invVisited) {
            vertex->path = previousVertex;
            hasIntersected = true;
            return true;
        }
        else if(isInverted && vertex->visited) {
            previousVertex->path = vertex;
            hasIntersected = true;
            return true;
        }
        return false;
}

template <class T> // Returns Intersecting Vertex
bool Dijkstra<T>::dijkstraShortestPathBi(const T &origin, const T &dest, bool isInverted) {
    auto s = findVertex(origin);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);

    Vertex<T>* prevVertex = nullptr;
    while(!q.empty()) {
        auto v = q.extractMin();

        if (isInverted)
            invDijkstraStep(q, v, prevVertex);
        else
            directDijkstraStep(q, v, prevVertex);

        if(hasIntersected)
            return true;

        prevVertex = v;
    }
    return false;
}

template<class T>
void Dijkstra<T>::directDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, Vertex<T>* previousVertex) const {
    for(auto e : v->outgoing) {
        auto oldDist = e->dest->dist;
        if (relax(v, e->dest, e.weight, previousVertex)) {
            if (oldDist == INF)
                q.insert(e->dest);
            else if(!hasIntersected)
                q.decreaseKey(e->dest);
        }
    }
}

template<class T>
void Dijkstra<T>::invDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, Vertex<T>* previousVertex) const {
    for(auto e : v->incoming) {
        auto oldDist = e->orig->dist;
        if (relaxInv(v, e->orig, e.weight, previousVertex)) {
            if (oldDist == INF)
                q.insert(e->orig);
            else if(!hasIntersected)
                q.decreaseKey(e->orig);
        }
    }
}

// ----------------------------- SINGLE THREAD ----------------------------- //

template<class T>
void Dijkstra<T>::directDijkstraStepSingle(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v) const {
    for(auto e : v->outgoing) {
        auto oldDist = e->dest->dist;
        if (relaxSingle(v, e->dest, e.weight)) {
            if (oldDist == INF)
                q.insert(e->dest);
            else
                q.decreaseKey(e->dest);
        }
    }
}

template<class T>
inline bool Dijkstra<T>::relaxSingle(Vertex<T> *v, Vertex<T> *w, double weight) {
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

        directDijkstraStepSingle(q, v);
    }
}


#endif //FIX_IT_DIJKSTRA_H
