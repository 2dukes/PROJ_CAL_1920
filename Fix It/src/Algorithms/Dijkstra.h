//
// Created by Rui Pinto on 5/20/2020.
//

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
    void dijkstraShortestPath(const T &origin, const T &dest);
};

template<class T>
Dijkstra<T>::Dijkstra(Graph<T> *graph) {
    this->graph = graph;
}

// ----------------------------- SINGLE THREAD ----------------------------- //


template <class T>
void Dijkstra<T>::dijkstraShortestPath(const T &origin, const T &dest) {

    // Vertex<T>* orig = graph->findVertex(origin);
    Vertex<T>* orig = graph->initPathAlg(origin);

    MutablePriorityQueue<Vertex<T>> vertexQueue;
    vertexQueue.insert(orig);

    while(!vertexQueue.empty()) {
        Vertex<T>* vertex = vertexQueue.extractMin();
        if(vertex->getInfo() == dest)
            break;

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

}

#endif //FIX_IT_DIJKSTRA_H
