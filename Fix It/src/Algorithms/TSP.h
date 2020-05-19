#ifndef FIX_IT_TSP_H
#define FIX_IT_TSP_H

#include "../Graph/Graph.h"
#include "AStar.h"

#include "vector"
#include "SearchAlgorithms.h"
#include "Dijkstra.h"

using namespace std;

template <class T>
class TSP {
    Graph<T>* graph;
    vector<T> visitOrder;
    vector<Vertex<T>*> poisVertices;
    vector<T> lastSolution;
    int visitOrderFinalSize;
    Vertex<T>* finishNode;
    Vertex<T>* startNode;

    void findBestVisitOrder(Vertex<T> *startVertex, Vertex<T> *endVertex);
    Vertex<T>* getClosestVertex(Vertex<T> *v, const vector<Vertex<T>*> &otherVertices) const;
    void buildSolution();

public:
    TSP(Graph<T>* graph);

    vector<T> calculatePath(const vector<T> &pois, T startNodeId, T endNodeId);


    // TODO: mudar de vectors para uma melhor estrutura de dados, por exemplo HashTable

    friend class Graph<T>;

};

template<class T>
TSP<T>::TSP(Graph<T>* graph) {
    this->graph = graph;
}

template<class T>
vector<T> TSP<T>::calculatePath(const vector<T> &pois, T startVertexId, T endVertexId) {

    //----------------------------------------Find and Check Vertices--------------------------------

    startNode = graph->findVertex(startVertexId);
    finishNode = graph->findVertex(endVertexId);

    if (startNode == NULL or finishNode == NULL) {
        cerr << "There is no such vertex" << endl;
        return {};
    }

    for (T vertexId: pois) {
        Vertex<T> *v = graph->findVertex(vertexId);
        if (v == NULL) {
            cerr << "There is no such vertex" << endl;
            return {};
        }
        poisVertices.push_back(v);
    }

    //-----------------------------------------------------------------------------------------------

    visitOrderFinalSize = 2 + pois.size(); // startVertex + pois + endVertex

    findBestVisitOrder(startNode, finishNode);

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
void TSP<T>::findBestVisitOrder(Vertex<T> *start, Vertex<T> *end) {
    SearchAlgorithm<T> searchAlgorithm(graph);
    vector<T> reachableVertices = searchAlgorithm.bfs(start->getInfo());

    // TODO verificar se o endVertex é alcançável

    // TODO verificar se os vertices de this->poisVertices são alcançáveis



    //--------------------------------All Vertices are reachable now---------------------------------

    visitOrder.push_back(start->getInfo());
    poisVertices.erase(std::remove(poisVertices.begin(), poisVertices.end(), start), poisVertices.end());

    Vertex<T> *closestVertex;
    vector<Vertex<T>*> poisToVisit = poisVertices;

    while(!poisToVisit.empty()) {
        closestVertex = getClosestVertex(startNode, poisToVisit);

        findBestVisitOrder(closestVertex, finishNode);

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
        poisVertices.push_back(start);
    }

}

template<class T>
Vertex<T>* TSP<T>::getClosestVertex(Vertex<T> *v, const vector<Vertex<T>*> &otherVertices) const {
    Vertex<T>* closestVertex = otherVertices.at(0);
    double closestVertexDistance = generalFunctions::heuristicDistance(v, closestVertex);
    double distance;

    for (Vertex<T>* vertex: otherVertices) {
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
    Dijkstra<T> dijkstra(graph);

    for (int i = 0;  i < visitOrder.size() - 1; i++) {
        dijkstra.dijkstraShortestPath(visitOrder.at(i), visitOrder.at(i+1));
        for (int j : graph->getPath(visitOrder.at(i), visitOrder.at(i+1))) {
            lastSolution.push_back(j);
        }

        if (i != visitOrder.size() - 2) {
            lastSolution.pop_back();
        }
    }

}

#endif //FIX_IT_TSP_H