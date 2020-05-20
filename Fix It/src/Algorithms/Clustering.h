
#ifndef FIX_IT_CLUSTERING_H
#define FIX_IT_CLUSTERING_H


#include "DijkstraBiDir.h"
#include "../Utils/NecessaryFunctions_NameSpaces.h"
#include <map>

template <class T>
struct destStruct{
    Vertex<T>* dest;
    double dist;
};

template <class T>
class Clustering {
    const Graph<T>* cityGraph;
public:
    Clustering(const Graph<T>* cityGraph);
    void calculateClustering(vector<T> auxPOIs);
    Vertex<T>* getClosestVertex(Vertex<T> *source, vector<Vertex<T> *>& POIs);
    double getFurthestVertex(Vertex<T>* source, vector<Vertex<T>*> POIs);
};

template<class T>
Clustering<T>::Clustering(const Graph<T> *cityGraph) {
        this->cityGraph = cityGraph;
}

template<class T>
void Clustering<T>::calculateClustering(vector<T> auxPOIs) { // Based on k-spanning Tree algorithm for clustering, but using an heuristic approach!
    for(Vertex<T>* v: cityGraph->getVertexSet())
        v->setVZone(ZONE0);
//    cout << auxPOIs.size() << endl;
    if(auxPOIs.size() == 1) {
        cityGraph->findVertex(auxPOIs.at(0))->setVZone(ZONE1);
        return;
    }

    vector<Vertex<T>*> POIs;
    vector<Vertex<T>*> POIsAux;
    map<T, destStruct<T>> nodeMinDistance;

    // Construct POIs vector...
    for(T idNode: auxPOIs) {
        POIs.push_back(cityGraph->findVertex(idNode));
        POIsAux.push_back(cityGraph->findVertex(idNode));
    }

    typedef typename vector<Vertex<T>*>::iterator iterator;
    typedef typename map<T, destStruct<T>>::iterator mapIT;
    vector<double> auxDistances;

    int num_clusters = (auxPOIs.size() <= 6 && auxPOIs.size() > 2) ? 1 : 2;

    Vertex<T>* cVertex;
    for(Vertex<T>* currVertex: POIs) {
        POIsAux = POIs;
        mapIT iTer;
        cVertex = getClosestVertex(currVertex, POIsAux);

        iTer = nodeMinDistance.find(cVertex->getInfo());
        while(true) {

            if(iTer != nodeMinDistance.end()) {
                if(iTer->second.dest->getInfo() != currVertex->getInfo())
                    break;
            }
            else {
                if(cVertex->getInfo() != currVertex->getInfo())
                    break;
            }
            for(iterator ith = POIsAux.begin(); ith != POIsAux.end(); ith++) {
                if((*ith)->getInfo() == cVertex->getInfo()) {
                    POIsAux.erase(ith);
                    break;
                }
            }
            cVertex = getClosestVertex(currVertex, POIsAux);
            iTer = nodeMinDistance.find(cVertex->getInfo());
        }
        destStruct<T> auxStruct;
        auxStruct.dest = cVertex;
        auxStruct.dist = generalFunctions::heuristicDistance(currVertex, cVertex);

        nodeMinDistance.insert(pair<T, destStruct<T>>(currVertex->getInfo(), auxStruct));

        auxDistances.push_back(auxStruct.dist);
    }
    sort(auxDistances.begin(), auxDistances.end());

    int borderDist = auxDistances.at(auxDistances.size() - num_clusters - 1);

    int zoneI = 1;
    auto zone = static_cast<MAP_ZONE>(zoneI);
    int vOccupied = 0;
    int numIter = 0;


    for(mapIT iterator = nodeMinDistance.begin(); iterator != nodeMinDistance.end(); iterator++) {
        cout << iterator->first << endl;
        if(iterator->second.dist < borderDist) {
            if(iterator->second.dest->getVZone() >= 1 && cityGraph->findVertex(iterator->first)->getVZone() == 0) {
                cityGraph->findVertex(iterator->first)->setVZone(iterator->second.dest->getVZone());
                cout << "ENTERED1\n";
            }
            else if (iterator->second.dest->getVZone() == 0 && cityGraph->findVertex(iterator->first)->getVZone() >= 1) {
                (iterator->second.dest)->setVZone(cityGraph->findVertex(iterator->first)->getVZone());
                cout << "ENTERED2\n";
            }
            else {
                cityGraph->findVertex(iterator->first)->setVZone(zone);
                (iterator->second.dest)->setVZone(zone);
                cout << "ENTERED3\n";
            }
            vOccupied++;
        }
        else {
            if(vOccupied != 0) {
                zone = static_cast<MAP_ZONE>(++zoneI);
                vOccupied = 0;
            }
            cityGraph->findVertex(iterator->first)->setVZone(zone);
            vOccupied++;
        }
        cout << zone << endl;
        numIter++;
    }

    for(T v: auxPOIs) {
        cout << cityGraph->findVertex(v)->getInfo() << " | " << cityGraph->findVertex(v)->getVZone() << endl;
    }

    for(Vertex<T>* v: cityGraph->getVertexSet()) {
        if(v->getVZone() >= 1 && v->getVZone() <= 3)
            cout << v->getInfo() << endl;
    }
    cout << numIter << endl;
}

template<class T>
Vertex<T>* Clustering<T>::getClosestVertex(Vertex<T> *source, vector<Vertex<T> *>& POIs) {
    typedef typename vector<Vertex<T>*>::iterator iterator;
    double minDist = INF, auxDist;
    Vertex<T>* toRetrieve;

    for(iterator iTr = POIs.begin(); iTr != POIs.end(); iTr++) {
        auxDist = generalFunctions::heuristicDistance(source, *iTr);
        if(auxDist < minDist) {
            minDist = auxDist;
            toRetrieve = *iTr;
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
