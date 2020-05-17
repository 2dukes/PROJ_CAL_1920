//
// Created by Rui Pinto on 5/16/2020.
//

#ifndef FIX_IT_PRIM_H
#define FIX_IT_PRIM_H
#include "../Graph/Graph.h"

template <class T>
class Prim {
    Graph<T>* cityGraph;
public:
    Prim(const Graph<T>* cityGraph);
    vector<Vertex<T>* > calculatePrim(Graph<T>* cityGraph);
};

template<class T>
Prim<T>::Prim(const Graph<T> *cityGraph) {
    this->cityGraph = cityGraph;
}

template<class T>
vector<Vertex<T>* > Prim<T>::calculatePrim(Graph<T>* cityGraph) {
    vector<Vertex<T>*> vertexSet = cityGraph->getVertexSet();
    for(Vertex<T>* v: vertexSet) {
        v->dist = INF;
        v->path = NULL;
        v->visited = false;
    }

    Vertex<T>* origin = vertexSet.at(0); // Arbitrary
    origin->dist = 0;

    MutablePriorityQueue<Vertex<T>> queue;
    queue.insert(origin);

    while(!queue.empty()) {
        Vertex<T>* v = queue.extractMin();
        v->visited = true;
        for(Edge<T> e: v->adj) {
            if(!e.dest->visited) {
                if(e.dest->dist > e.weight) {
                    bool belongsToQueue = true;
                    if(e.dest->dist == INF)
                        belongsToQueue = false;

                    e.dest->dist = e.weight;
                    e.dest->path = v;

                    if(belongsToQueue)
                        queue.decreaseKey(e.dest);
                    else
                        queue.insert(e.dest);
                }
            }
        }
    }

    return vertexSet;
}

#endif //FIX_IT_PRIM_H
