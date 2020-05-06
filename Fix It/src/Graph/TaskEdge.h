#ifndef FIX_IT_TASKEDGE_H
#define FIX_IT_TASKEDGE_H

#include "Graph.h"

// TODO -> To be used in Stable marriage (Bipartite Graph)

template <class T>
class TaskEdge : public Edge<T> {
    double capacity;
    double flow;
public:
    TaskEdge(Vertex<T> *o, Vertex<T> *d, double c, double w = 0, double f = 0); // Careful with constructor's order
    double getFlow() const;
    double getCapacity() const;
};

template <class T>
TaskEdge<T>::TaskEdge(Vertex<T> *o, Vertex<T> *d, double c, double w, double f): Edge<T>(o, d, w), capacity(c), flow(f) { }

template <class T>
double TaskEdge<T>::getFlow() const {
    return flow;
}

template <class T>
double TaskEdge<T>::getCapacity() const {
    return capacity;
}


#endif //FIX_IT_TASKEDGE_H
