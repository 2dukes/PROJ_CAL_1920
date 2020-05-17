//
// Created by Tiago on 16/05/2020.
//

#ifndef FIX_IT_TSP_H
#define FIX_IT_TSP_H

#include "../Graph/Graph.h"
#include "AStar.h"

#include "vector"
#include "SearchAlgorithms.h"

using namespace std;

template <class T>
class TSP {
    Graph<T>* graph;
    vector<T> visitOrder;
    vector<Vertex<T>> poisVertices;
    vector<Vertex<T>> lastSolution;
    int visitOrderFinalSize;

    void findBestVisitOrder(const Vertex<T> &startVertex, const Vertex<T> &endVertex);
    Vertex<T> getClosestVertex(const Vertex<T> &v, const vector<Vertex<T>> &otherVertices) const;
    void buildSolution();

public:
    TSP(const Graph<T>* graph);

    vector<T> calculatePath(const vector<T> &pois, T startNodeId, T endNodeId);


    // TODO: mudar de vectors para uma melhor estrutura de dados, por exemplo HashTable



};

template<class T>
TSP<T>::TSP(const Graph<T>* graph) {
    this->graph = graph;
}

template<class T>
vector<T> TSP<T>::calculatePath(const vector<T> &pois, T startVertexId, T endVertexId) {

    //----------------------------------------Find and Check Vertices--------------------------------

    Vertex<T> startVertex = graph->findVertex(startVertexId);
    Vertex<T> endVertex = graph->findVertex(endVertexId);

    if (startVertex == NULL or endVertex == NULL) {
        cerr << "There is no such vertex" << endl;
        return {};
    }

    for (T &vertexId: pois) {
        Vertex<T> v = graph->findVertex(vertexId);
        if (v == NULL) {
            cerr << "There is no such vertex" << endl;
            return {};
        }
        poisVertices.push_back(v);
    }

    //-----------------------------------------------------------------------------------------------

    visitOrderFinalSize = 2 + pois.size(); // startVertex + pois + endVertex

    findBestVisitOrder(startVertex, endVertex);

    visitOrder.push_back(endVertexId);

    if (visitOrder.size() != visitOrderFinalSize) {
        lastSolution.clear();
        return lastSolution;
    }
    else {
        buildSolution();
        return lastSolution;
    }


}

template<class T>
void TSP<T>::findBestVisitOrder(const Vertex<T> &startVertex, const Vertex<T> &endVertex) {
    SearchAlgorithm<T> searchAlgorithm(graph);
    vector<T> reachableVertices = searchAlgorithm.bfs(startVertex.getInfo());

    // TODO verificar se o endVertex é alcançável

    // TODO verificar se os vertices de this->poisVertices são alcançáveis



    //--------------------------------All Vertices are reachable now---------------------------------

    visitOrder.push_back(startVertex.getId());
    poisVertices.erase(std::remove(poisVertices.begin(), poisVertices.end(), startVertex), poisVertices.end());

    Vertex<T> closestVertex;
    vector<Vertex<T>> poisToVisit = poisVertices;

    while(!poisToVisit.empty()) {
        closestVertex = getClosestVertex(startVertex, poisToVisit);

        findBestVisitOrder(closestVertex, endVertex);

        if (visitOrder.size() != visitOrderFinalSize - 1) {
            poisVertices.erase(std::remove(poisVertices.begin(), poisVertices.end(), closestVertex), poisVertices.end());
        }
        else {
            return;
        }
    }

    // Back-tracking
    if (visitOrder.size() != visitOrderFinalSize - 1) {
        visitOrder.pop_back();
        poisVertices.insert(startVertex);
    }
}

template<class T>
Vertex<T> TSP<T>::getClosestVertex(const Vertex<T> &v, const vector<Vertex<T>> &otherVertices) const {
    Vertex<T> closestVertex = *(otherVertices.at(0));
    double closestVertexDistance = generalFunctions::heuristicDistance(v, closestVertex);
    double distance;

    for (auto &vertex: otherVertices) {
        distance = generalFunctions::heuristicDistance(v, vertex);
        if (distance < closestVertexDistance) {
            closestVertex = vertex;
            closestVertexDistance = distance;
        }
    }

    return closestVertex;
}

template<class T>
void TSP<T>::buildSolution() {
    AStar<T> aStar(graph);

    for (int i = 0;  i < visitOrder.size() - 1; i++) {
        for (int j : aStar.AStarShortestPath(visitOrder.at(i), visitOrder.at(i+1))) {
            lastSolution.push_back(i);
        }

        if (i != visitOrder.size() - 2) {
            lastSolution .pop_back();
        }
    }

}

#endif //FIX_IT_TSP_H
