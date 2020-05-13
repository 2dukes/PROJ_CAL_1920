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
    bool relaxInv(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t);
    bool isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex);
    double heuristicDistance(Vertex<T>* origin, Vertex<T>* dest);
    void AStarStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T> *t) const;
    void AStarStepInv(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T> *t) const;

    void AStarShortestPathBi(const T &origin, const T &dest, bool isInverted);

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
        w->visited = true;
        return true;
    }
    else
        return false;
}

template<class T>
inline bool AStar<T>::relaxInv(Vertex<T> *v, Vertex<T> *w, double weight, Vertex<T>* t) {
    if (v->weight + weight + heuristicDistance(w, t) < w->weight) {
        w->dist = v->weight + weight;
        w->weight = v->weight + weight + heuristicDistance(w, t);
        v->path = w; // Careful!
        w->invVisited = true;
        return true;
    }
    else
        return false;
}

template<class T>
void AStar<T>::AStarStep(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T>* t) const {
    for (auto e : v->outgoing) {
        if (relax(v, e->dest, e.weight, t)) {
            if (!q.find(e->dest))
                q.insert(e->dest);
            else
                q.decreaseKey(e->dest);
        }
    }
}

template<class T>
void AStar<T>::AStarStepInv(MutablePriorityQueue<Vertex<T>> &q, const Vertex<T> *v, const Vertex<T>* t) const {
    for (auto e : v->incoming) {
        if (relaxInv(v, e->orig, e.weight, t)) {
            if (!q.find(e->orig))
                q.insert(e->orig);
            else
                q.decreaseKey(e->orig);
        }
    }
}

template <class T>
bool AStar<T>::isIntersecting(Vertex<T>* vertex, bool isInverted, Vertex<T>* previousVertex) {
    if(vertex->invVisited && vertex->visited) {
        if(!isInverted)
            vertex->path = previousVertex;
        else
            previousVertex->path = vertex;
        return true;
    }
    return false;
}

template<class T>
void AStar<T>::AStarShortestPathBi(const T &origin, const T &dest, bool isInverted) {
    auto t = findVertex(dest); // Destination Vertex
    auto s = graph->initPathAlg(origin);

    MutablePriorityQueue<Vertex<T>> q; // Ordered by gScore
    q.insert(s);
    
    Vertex<T>* prevVertex = nullptr;
    while(!q.empty()) {
        auto v = q.extractMin();

        if(isIntersecting(v, isInverted, prevVertex))
            return v;

        if(isInverted)
            AStarStepInv(q, v, t);
        else
            AStarStep(q, v, t);
        prevVertex = v;
    }
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

        AStarStep(q, v, t);
    }
}


#endif //FIX_IT_ASTAR_H
