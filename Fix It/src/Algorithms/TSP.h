//
// Created by Tiago on 16/05/2020.
//

#ifndef FIX_IT_TSP_H
#define FIX_IT_TSP_H

#include "../Graph/Graph.h"
#include "AStar.h"

#include "vector"

using namespace std;

template <class T>
class TSP {
    Graph<T>* graph;
    vector<T> visitOrder;

    void findBestVisitOrder(const Vertex<T> &startVertex, const Vertex<T> &endVertex);


public:
    TSP(const Graph<T>* graph);

    vector<T> calculatePath(const vector<T> &pois, T startNodeId, T endNodeId);


};

template<class T>
TSP<T>::TSP(const Graph<T>* graph) {
    this->graph = graph;
}

template<class T>
vector<T> TSP<T>::calculatePath(const vector<T> &pois, T startVertexId, T endVertexId) {

    //----------------------------------------Find and Check Vertices--------------------------------

    Vertex<T> startVertex = graph->findVertex(startVertex);
    Vertex<T> endVertex = graph->findVertex(endVertexId);

    if (startVertex == NULL or endVertex == NULL) {
        cerr << "There is no such vertex" << endl;
        return {};
    }

    vector<Vertex<T>> poisVerteces;

    for (T &vertexId: pois) {
        Vertex<T> v = graph->findVertex(vertexId);
        if (v == NULL) {
            cerr << "There is no such vertex" << endl;
            return {};
        }
        poisVerteces.push_back(v);
    }

    //-----------------------------------------------------------------------------------------------

    int visitOrderFinalSize = 2 + pois.size(); // startVertex + pois + endVertex

    //findBestVisitOrder(stardNodeId, endNodeId)
}

template<class T>
void TSP<T>::findBestVisitOrder(const Vertex<T> &startVertex, const Vertex<T> &endVertex) {

}

#endif //FIX_IT_TSP_H
