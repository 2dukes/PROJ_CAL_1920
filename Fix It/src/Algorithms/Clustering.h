
#ifndef FIX_IT_CLUSTERING_H
#define FIX_IT_CLUSTERING_H


#include "DijkstraBiDir.h"
#include "../Utils/NecessaryFunctions_NameSpaces.h"
#include <map>

#define MIN_DIST 500

template <class T>
typedef struct destStruct {
    Vertex<T>* dest;
    double dist;
};

template <class T>
class Clustering {
    Graph<T>* cityGraph;
public:
    Clustering(Graph<T>* cityGraph);
    void calculateClustering(vector<T> auxPOIs);
    typename vector<Vertex<T>*>::iterator getClosestVertex(Vertex<T>* source, vector<Vertex<T>*> POIs);
    double getFurthestVertex(Vertex<T>* source, vector<Vertex<T>*> POIs);
};

template<class T>
Clustering<T>::Clustering(Graph<T> *cityGraph) {
        this->cityGraph = cityGraph;
}

template<class T>
void Clustering<T>::calculateClustering(vector<T> auxPOIs) { // Based on k-spanning Tree algorithm for clustering, but using an heuristic approach!
    if(auxPOIs.size() == 1) {
        cityGraph->findVertex(auxPOIs.at(0))->setvZone(ZONE1);
        return;
    }

    vector<Vertex<T>*> POIs;
    map<T, destStruct<T>> nodeMinDistance;

    // Construct POIs vector...
    for(Vertex<T> idNode: auxPOIs)
        POIs.push_back(cityGraph->findVertex(idNode));

    typedef typename vector<Vertex<T>*>::iterator iterator;
    Vertex<T>* currVertex = POIs.at(0);
    iterator iTr = POIs.begin();
    vector<T> auxDistances;

    int num_clusters = 1; // Actuallu number of Edges to remove... Num clusters is equivalente to +1...
    if(getFurthestVertex(currVertex, POIs) > MIN_DIST) {
        num_clusters = (auxPOIs.size() <= 6 && auxPOIs.size() > 2) ? 2 : 3;
        num_clusters = auxPOIs.size() > 10  ? 4 : 3;
    }

    while(POIs.size() > 1) {
        POIs.erase(iTr);
        iTr = getClosestVertex(currVertex);

        destStruct<T> auxStruct;
        auxStruct.dest = *iTr;
        auxStruct.dist = generalFunctions::heuristicDistance(currVertex, *iTr);
        nodeMinDistance.insert(pair<T, destStruct<T>>(currVertex->getInfo(), auxStruct));

        auxDistances.push_back(generalFunctions::heuristicDistance(currVertex, *iTr));
        currVertex = *iTr;
    }
    sort(auxDistances.begin(), auxDistances.end());

    int borderDist = auxDistances.at(auxDistances.size() - num_clusters);

    typedef typename map<T, double>::iterator mapIT;
    int zoneI = 0;
    auto zone = static_cast<MAP_ZONE>(zoneI);
    for(mapIT iterator = nodeMinDistance.begin(); iterator != nodeMinDistance.end(); iterator++) {
        if(iterator->second.dist < borderDist) {
            cityGraph->findVertex(iterator->first)->setvZone(zone);
            cityGraph->findVertex(iterator->second.dest)->setvZone(zone);
        }
        else {
            zone = static_cast<MAP_ZONE>(++zoneI);
            cityGraph->findVertex(iterator->second.dest)->setvZone(zone);
        }
    }
}

template<class T>
typename vector<Vertex<T>*>::iterator Clustering<T>::getClosestVertex(Vertex<T> *source, vector<Vertex<T> *> POIs) {
    typedef typename vector<Vertex<T>*>::iterator iterator;
    double minDist = INF, auxDist;
    iterator toRetrieve;

    for(iterator iTr = POIs.begin(); iTr != POIs.end(); iTr++) {
        auxDist = generalFunctions::heuristicDistance(source, *iTr);
        if(auxDist < minDist) {
            minDist = auxDist;
            toRetrieve = iTr;
        }
    }
    return toRetrieve;
}

template<class T>
double Clustering<T>::getFurthestVertex(Vertex<T> *source, vector<Vertex<T> *> POIs) {
    typedef typename vector<Vertex<T>*>::iterator iterator;
    double maxDist = -INF, auxDist;

    for(iterator iTr = POIs.begin(); iTr != POIs.end(); iTr++) {
        auxDist = generalFunctions::heuristicDistance(source, *iTr);
        if(auxDist > maxDist)
            maxDist = auxDist;
    }
    return maxDist;
}


#endif //FIX_IT_CLUSTERING_H