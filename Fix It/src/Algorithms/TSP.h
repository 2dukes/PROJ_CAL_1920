#ifndef FIX_IT_TSP_H
#define FIX_IT_TSP_H

#include "../Graph/Graph.h"
#include "AStar.h"

#include "vector"
#include "SearchAlgorithms.h"
#include "Dijkstra.h"

using namespace std;

enum SEARCH_ALGORITHM {DIJKSTRA = 0, ASTAR = 1};

template <class T>
class TSP {
    Graph<T>* graph;
    vector<T> visitOrder;
    vector<Vertex<T>*> poisVertices;
    vector<T> lastSolution;
    int visitOrderFinalSize;
    Vertex<T>* finishNode;
    Vertex<T>* startNode;
    SEARCH_ALGORITHM searchAlgorithm;

    void findBestVisitOrder(Vertex<T> *startVertex);
    Vertex<T>* getClosestVertex(Vertex<T> *v, const vector<Vertex<T>*> &POIs) const;
    void buildSolutionDijkstra();
    void buildSolutionAStar();
    void buildSolution();


public:
    TSP(Graph<T>* graph, SEARCH_ALGORITHM searchAlgorithm);

    vector<T> calculatePath(const vector<T> &pois, T startNodeId, T endNodeId);

    friend class Graph<T>;

};

template<class T>
TSP<T>::TSP(Graph<T>* graph, SEARCH_ALGORITHM searchAlgorithm) {
    this->graph = graph;
    this->searchAlgorithm = searchAlgorithm;
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

    findBestVisitOrder(startNode);

    visitOrder.push_back(endVertexId); // finish the path in the endVertex

    if (visitOrder.size() != visitOrderFinalSize) { // se a ordem de visita não contem todos os pontos de interesse
        return {};
    }
    else { // se a ordem de visita contem todos os pontos de interesse, construir caminho
        buildSolution();
        return lastSolution;
    }


}

template<class T>
void TSP<T>::findBestVisitOrder(Vertex<T> *start) {
    SearchAlgorithm<T> searchAlgorithm(graph);
    vector<T> reachableVertices = searchAlgorithm.bfs(start->getInfo()); // vértices alcançáveis a partir do vértice de início

    // Mover o vértice de início do vetor visitOrder para poisVertices
    visitOrder.push_back(start->getInfo());
    poisVertices.erase(std::remove(poisVertices.begin(), poisVertices.end(), start), poisVertices.end());

    Vertex<T> *closestVertex;
    
    vector<Vertex<T>*> poisToVisit = poisVertices;

    while(!poisToVisit.empty()) { // enquanto ainda há pontos de interesse para visitar
        closestVertex = getClosestVertex(startNode, poisToVisit); // vértice mais próximo do vértice de início

        findBestVisitOrder(closestVertex);

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
Vertex<T>* TSP<T>::getClosestVertex(Vertex<T> *v, const vector<Vertex<T>*> &POIs) const { // retorna o ponto de interesse mais próximo do vértice v
    Vertex<T>* closestVertex = POIs.at(0);
    double closestVertexDistance = generalFunctions::heuristicDistance(v, closestVertex);
    double distance;

    for (Vertex<T>* vertex: POIs) {
        distance = generalFunctions::heuristicDistance(v, vertex);
        if (distance < closestVertexDistance) {
            closestVertex = vertex;
            closestVertexDistance = distance;
        }
    }

    return closestVertex;
}


template<class T>
void TSP<T>::buildSolutionDijkstra() {

    Dijkstra<T> dijkstra(graph);

    for (int i = 0;  i < visitOrder.size() - 1; i++) {

        dijkstra.dijkstraShortestPath(visitOrder.at(i), visitOrder.at(i+1)); // encontrar o melhor caminho entre os dois vértices

        for (int j : graph->getPath(visitOrder.at(i), visitOrder.at(i+1))) {
            lastSolution.push_back(j); // adicionar o caminho entre os dois vértices à solução
        }

        if (i != visitOrder.size() - 2) { // para não repetir o segundo vértice adicionado
            lastSolution.pop_back();
        }
    }
}

template<class T>
void TSP<T>::buildSolutionAStar() {

    AStar<T> astar(graph);

    for (int i = 0;  i < visitOrder.size() - 1; i++) {

        astar.AStarShortestPath(visitOrder.at(i), visitOrder.at(i+1)); // encontrar o melhor caminho entre os dois vértices

        for (int j : graph->getPath(visitOrder.at(i), visitOrder.at(i+1))) { // adicionar o caminho entre os dois vértices à solução
            lastSolution.push_back(j);
        }

        if (i != visitOrder.size() - 2) { // para não repetir o segundo vértice adicionado
            lastSolution.pop_back();
        }
    }
}

template<class T>
void TSP<T>::buildSolution() {
    if (searchAlgorithm == DIJKSTRA) {
        buildSolutionDijkstra();
    }
    else if (searchAlgorithm == ASTAR) {
        buildSolutionAStar();
    }
}




#endif //FIX_IT_TSP_H