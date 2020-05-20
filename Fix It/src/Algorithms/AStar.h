#ifndef FIX_IT_ASTARA_H
#define FIX_IT_ASTARA_H


#include <math.h>
#include "../Utils/NecessaryFunctions_NameSpaces.h"

template <class T>
class AStar { // TODO TEST A* ALGORITHM USING CLASSES TESTS! -> SHOULD GIVE AND APROXIMATE/SAME RESULT! Probably Vertex<T> will be substituted by AVertex! Or make a cast...
protected:
    Graph<T>* graph;

public:
    AStar(Graph<T>* graph);

    // ----------------------------- SINGLE THREAD ----------------------------- //

    void AStarShortestPath(const T &origin, const T &dest);
    bool relaxSingle(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t);
    void AStarStepSingle(MutablePriorityQueue<Vertex<T>> &q, Vertex<T> *v, Vertex<T> *t);

};

template<class T>
AStar<T>::AStar(Graph<T> *graph) {
    this->graph = graph;
}


// ----------------------------- SINGLE THREAD ----------------------------- //

template<class T>
void AStar<T>::AStarStepSingle(MutablePriorityQueue<Vertex<T>> &q, Vertex<T> *v, Vertex<T>* t) {
    for (auto e : v->outgoing) {
        auto oldDist = e->dest->weight;
        if (relaxSingle(v, e->dest, e->weight, t)) {
            if (oldDist == INF)
                q.insert(e->dest);
            else
                q.decreaseKey(e->dest);
        }
    }
}

template<class T>
inline bool AStar<T>::relaxSingle(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t) {
    if (v->weight + weight + generalFunctions::heuristicDistance(w, t) < w->weight) {
        w->dist = v->weight + weight;
        w->weight = v->weight + weight + generalFunctions::heuristicDistance(w, t);
        w->path = v;
        w->visited = true;
        return true;
    }
    else
        return false;
}

template<class T>
void AStar<T>::AStarShortestPath(const T &origin, const T &dest) {
    auto t = graph->findVertex(dest); // Destination Vertex
    auto s = graph->initPathAlg(origin);

    MutablePriorityQueue<Vertex<T>> q; // Ordered by gScore
    q.insert(s);
    while(!q.empty()) {
        Vertex<T>* v = q.extractMin();
        v->visited = true;

        if(v->getInfo() == dest)
            break;

        AStarStepSingle(q, v, t);
    }
}


#endif //FIX_IT_ASTARA_H
