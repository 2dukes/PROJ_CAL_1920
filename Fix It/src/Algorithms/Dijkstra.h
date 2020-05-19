#ifndef FIX_IT_DIJKSTRA_H
#define FIX_IT_DIJKSTRA_H

#include <chrono>
#include "../Graph/Graph.h"

template <class T>
class Dijkstra {
protected:
    Graph<T>* graph;

public:
    Dijkstra(Graph<T>* graph);

    // ----------------------------- MULTI THREAD ----------------------------- //

//    bool dijkstraShortestPathBi(const T &origin, const T &dest, bool isInverted);
//    bool isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex);
//    bool relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* previousVertex);
//    bool relaxInv(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* previousVertex);
//    void invDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, Vertex<T> *v, Vertex<T>* previousVertex);
//    void directDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, Vertex<T> *v, Vertex<T>* previousVertex);

    // ----------------------------- SINGLE THREAD ----------------------------- //

    void dijkstraShortestPath(const T &origin, const T &dest);
    bool relaxSingle(Vertex<T> *v, Vertex<T> *w, double weight);
    void directDijkstraStepSingle(MutablePriorityQueue<Vertex<T>> &q, Vertex<T> *v);

    bool hasIntersected;
    friend class Graph<T>;
};

template<class T>
Dijkstra<T>::Dijkstra(Graph<T> *graph) {
    this->graph = graph;
}

// ----------------------------- SINGLE THREAD ----------------------------- //

template<class T>
void Dijkstra<T>::directDijkstraStepSingle(MutablePriorityQueue<Vertex<T>> &q, Vertex<T> *v) {
    for(auto e : v->outgoing) {
        auto oldDist = e->dest->weight;
        if (relaxSingle(v, e->dest, e->weight)) {
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
    for(Vertex<T> * vertex: graph->getVertexSet()) {
        vertex->weight = INF;
        vertex->path = nullptr;
    }

    Vertex<T>* orig = graph->findVertex(origin);
    orig->weight = 0;

    MutablePriorityQueue<Vertex<T>> vertexQueue;
    vertexQueue.insert(orig);

    while(!vertexQueue.empty()) {
        Vertex<T>* vertex = vertexQueue.extractMin();

        for(Edge<T>* edge: vertex->getOutgoingEdges()) {
            auto oldDist = edge->dest->weight;
            if(edge->dest->weight > vertex->weight + edge->weight) { // Means that edge.dest can be updated to a smaller value.
                edge->dest->weight = vertex->weight + edge->weight;
                edge->dest->path = vertex;
                if(oldDist == INF) // If element not in queue
                    vertexQueue.insert(edge->dest);
                else // If element in queue -> Push element to the top...
                    vertexQueue.decreaseKey(edge->dest);
            }
        }
    }
//    auto t = graph->findVertex(dest); // Destination Vertex
//    auto s = graph->initPathAlg(origin);
//    cout << s->getInfo() << endl;
//    cout << t->getInfo() << endl;
//    MutablePriorityQueue<Vertex<T>> q;
//    q.insert(s);
//    while(!q.empty()) {
//        auto v = q.extractMin();
//
//        if(v->getInfo() == t->getInfo())
//            break;
//
//        directDijkstraStepSingle(q, v);
//    }
}

// ----------------------------- MULTI THREAD ----------------------------- //

//template<class T>
//inline bool Dijkstra<T>::relaxInv(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* previousVertex) {
//    if (v->weight + weight < w->weight && !hasIntersected) {
//        if(isIntersecting(v, true, previousVertex))
//            return false;
//        else {
//            w->weight = v->weight + weight;
//            v->path = w; // Careful... Path Goes
//            w->invVisited = true;
//            return true;
//        }
//    }
//    return false;
//}
//template<class T>
//inline bool Dijkstra<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* previousVertex) {
//    if(v->weight + weight < w->weight && !hasIntersected) {
//        if(isIntersecting(v, false, previousVertex))
//            return false;
//        else {
//            w->weight = v->weight + weight;
//            w->path = v;
//            w->visited = true;
//            return true;
//        }
//    }
//    return false;
//}
//
//template <class T>
//bool Dijkstra<T>::isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex) {
//        if(!isInverted && vertex->invVisited) {
//            vertex->path = previousVertex;
//            hasIntersected = true;
//            return true;
//        }
//        else if(isInverted && vertex->visited) {
//            previousVertex->path = vertex;
//            hasIntersected = true;
//            return true;
//        }
//        return false;
//}
//
//template <class T> // Returns Intersecting Vertex
//bool Dijkstra<T>::dijkstraShortestPathBi(const T &origin, const T &dest, bool isInverted) {
//    auto s = findVertex(origin);
//    MutablePriorityQueue<Vertex<T>> q;
//    q.insert(s);
//
//    Vertex<T>* prevVertex = nullptr;
//    while(!q.empty()) {
//        auto v = q.extractMin();
//
//        if (isInverted)
//            invDijkstraStep(q, v, prevVertex);
//        else
//            directDijkstraStep(q, v, prevVertex);
//
//        if(hasIntersected)
//            return true;
//
//        prevVertex = v;
//    }
//    return false;
//}
//
//template<class T>
//void Dijkstra<T>::directDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, Vertex<T> *v, Vertex<T>* previousVertex) {
//    for(auto e : v->outgoing) {
//        auto oldDist = e->dest->dist;
//        if (relax(v, e->dest, e.weight, previousVertex)) {
//            if (oldDist == INF)
//                q.insert(e->dest);
//            else if(!hasIntersected)
//                q.decreaseKey(e->dest);
//        }
//    }
//}
//
//template<class T>
//void Dijkstra<T>::invDijkstraStep(MutablePriorityQueue<Vertex<T>> &q, Vertex<T> *v, Vertex<T>* previousVertex) {
//    for(auto e : v->incoming) {
//        auto oldDist = e->orig->dist;
//        if (relaxInv(v, e->orig, e.weight, previousVertex)) {
//            if (oldDist == INF)
//                q.insert(e->orig);
//            else if(!hasIntersected)
//                q.decreaseKey(e->orig);
//        }
//    }
//}


#endif //FIX_IT_DIJKSTRA_H
