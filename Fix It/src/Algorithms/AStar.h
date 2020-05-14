//
// Created by Rui Pinto on 5/6/2020.
//

#ifndef FIX_IT_ASTAR_H
#define FIX_IT_ASTAR_H

#include <math.h>
#include "../Utils/NecessaryFunctions_NameSpaces.h"

template <class T>
class AStar { // TODO TEST A* ALGORITHM USING CLASSES TESTS! -> SHOULD GIVE AND APROXIMATE/SAME RESULT! Probably Vertex<T> will be substituted by AVertex! Or make a cast...
protected:
    Graph<T>* graph;

public:
    AStar(const Graph<T>* graph);

    // ----------------------------- MULTI THREAD ----------------------------- //

    bool relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t, Vertex<T>* previousVertex);
    bool relaxInv(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t, Vertex<T>* previousVertex);
    bool isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex);
    void AStarStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T> *t, Vertex<T>* previousVertex) const;
    void AStarStepInv(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T> *t, Vertex<T>* previousVertex) const;
    bool AStarShortestPathBi(const T &origin, const T &dest, bool isInverted);

    // ----------------------------- SINGLE THREAD ----------------------------- //

    void AStarShortestPath(const T &origin, const T &dest);
    bool relaxSingle(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t);
    void AStarStepSingle(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T> *t) const;


    bool hasIntersected;
    friend class Graph<T>;
};

template<class T>
AStar<T>::AStar(const Graph<T> *graph) {
    this->graph = graph;
}

// ----------------------------- MULTI THREAD ----------------------------- //


template<class T>
inline bool AStar<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t, Vertex<T>* previousVertex) {
    if (v->weight + weight + generalFunctions::heuristicDistance(w, t) < w->weight && !hasIntersected) {
        if(isIntersecting(v, false, previousVertex))
            return false;
        else {
            w->dist = v->weight + weight;
            w->weight = v->weight + weight + generalFunctions::heuristicDistance(w, t);
            w->path = v;
            w->visited = true;
            return true;
        }
    }
    else
        return false;
}

template<class T>
inline bool AStar<T>::relaxInv(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t, Vertex<T>* previousVertex) {
    if (v->weight + weight + generalFunctions::heuristicDistance(w, t) < w->weight && !hasIntersected) {
        if(isIntersecting(v, true, previousVertex))
            return false;
        else {
            w->dist = v->weight + weight;
            w->weight = v->weight + weight + generalFunctions::heuristicDistance(w, t);
            v->path = w; // Careful!
            w->invVisited = true;
            return true;
        }
    }
    else
        return false;
}

template<class T>
void AStar<T>::AStarStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T>* t, Vertex<T>* previousVertex) const {
    for (auto e : v->outgoing) {
        if (relax(v, e->dest, e.weight, t, previousVertex)) {
            if (!q.find(e->dest))
                q.insert(e->dest);
            else if(!hasIntersected)
                q.decreaseKey(e->dest);
        }
    }
}

template<class T>
void AStar<T>::AStarStepInv(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T>* t, Vertex<T>* previousVertex) const {
    for (auto e : v->incoming) {
        if (relaxInv(v, e->orig, e.weight, t, previousVertex)) {
            if (!q.find(e->orig))
                q.insert(e->orig);
            else if(!hasIntersected)
                q.decreaseKey(e->orig);
        }
    }
}

template<class T>
bool AStar<T>::AStarShortestPathBi(const T &origin, const T &dest, bool isInverted) {
    auto t = findVertex(dest); // Destination Vertex
    auto s = graph->initPathAlg(origin);

    MutablePriorityQueue<Vertex<T>> q; // Ordered by gScore
    q.insert(s);

    Vertex<T>* prevVertex = nullptr;
    while(!q.empty()) {
        auto v = q.extractMin();

        if(isInverted)
            AStarStepInv(q, v, t, prevVertex);
        else
            AStarStep(q, v, t, prevVertex);

        if(hasIntersected)
            return true;

        prevVertex = v;
    }
    return false;
}

template <class T>
bool AStar<T>::isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex) {
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

// ----------------------------- SINGLE THREAD ----------------------------- //

template<class T>
void AStar<T>::AStarStepSingle(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T>* t) const {
    for (auto e : v->outgoing) {
        if (relaxSingle(v, e->dest, e.weight, t)) {
            if (!q.find(e->dest))
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
    auto t = findVertex(dest); // Destination Vertex
    auto s = graph->initPathAlg(origin);

    MutablePriorityQueue<Vertex<T>> q; // Ordered by gScore
    q.insert(s);
    while(!q.empty()) {
        auto v = q.extractMin();
        v->visited = true;

        if(v->getInfo() == t->getInfo())
            break;

        AStarStepSingle(q, v, t);
    }
}

#endif //FIX_IT_ASTAR_H
