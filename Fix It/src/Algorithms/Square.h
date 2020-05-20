#ifndef FIX_IT_SQUARE_H
#define FIX_IT_SQUARE_H

#include <Utils/NecessaryFunctions_NameSpaces.h>
#include "../Graph/Graph.h"

template <class T>
class Square {
    Graph<T>* graph;

public:
    Square(Graph<T>* graph);
    void calculateSquare(vector<T> POIs);
    double minX, minY, maxX, maxY;
};

template <class T>
Square<T>::Square(Graph<T> *graph) : graph(graph), minX(INF), minY(INF), maxX(-INF), maxY(-INF) { }

template <class T>
void Square<T>::calculateSquare(vector<T> POIs) {
    vector<Vertex<T>*> POIsAux;
    for(T id: POIs)
        POIsAux.push_back(graph->findVertex(id));

    for(Vertex<T>* vertex: POIsAux)
        generalFunctions::processCoordinates(vertex->getX(), vertex->getY(), minX, minY, maxX, maxY);

    printf("MaxX: %lf | MaxY: %lf | MinX: %lf | MinY: %lf\n", maxX, maxY, minX, minY);
    double halfX = (maxX + minX) / 2;
    double halfY = (maxY + minY) / 2;
    printf("HALFX: %lf | HALFY: %lf \n", halfX, halfY);

    for(auto vertex: POIsAux) {
        if(vertex->getX() >= halfX) {
            if(vertex->getY() >= halfY) // ZONE TOP_RIGHT
                vertex->setVZone(ZONE1);
            else                       // ZONE BOTTOM_RIGHT
                vertex->setVZone(ZONE3);
        }
        else {
            if(vertex->getY() >= halfY)  // ZONE TOP_LEFT
                vertex->setVZone(ZONE2);
            else                        // ZONE BOTTOM_LEFT
                vertex->setVZone(ZONE4);
        }
    }
}


#endif //FIX_IT_SQUARE_H
