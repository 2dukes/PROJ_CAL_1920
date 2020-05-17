#ifndef FIX_IT_GRAPHINTERFACE_H
#define FIX_IT_GRAPHINTERFACE_H

#include "Graph/Graph.h"
#include "../lib/graphviewer.h"
#include <unistd.h>

#define PRECISION 10e9

class GraphInterface {
    GraphViewer *graphViewer;
    int width;
    int height;
    double maxX;
    double maxY;
    double minX;
    double minY;

    double calculateX(double coord);
    double calculateY(double coord);

public:
    GraphInterface(int width, int height);

    template <class T>
    void displayPath(vector<Vertex<T> *> nodesPath);

    template<class T>
    void displayOporto(vector<Edge<T> *> edgesPath);
};

template <class T>
void GraphInterface::displayPath(vector<Vertex<T> *> nodesPath) {
    this->graphViewer= new GraphViewer(width, height, false);
    // graphViewer->setBackground(MAP_BACKGROUND);
    graphViewer->createWindow(this->width, this->height);
    int edgeID = 0;

    for(int vIndex = 0; vIndex < nodesPath.size() - 1; vIndex++) {
        Vertex<T>* auxVertex = nodesPath[vIndex];
        Vertex<T>* nextAuxVertex = nodesPath[vIndex + 1];
        graphViewer->addNode(auxVertex->getInfo(), calculateX(auxVertex->getX()), calculateY(auxVertex->getY()));
        graphViewer->addNode(nextAuxVertex->getInfo(), calculateX(nextAuxVertex->getX()), calculateY(nextAuxVertex->getY()));
        graphViewer->addEdge(edgeID++, auxVertex->getInfo(), nextAuxVertex->getInfo(), EdgeType::DIRECTED);
    }
    graphViewer->setVertexColor(nodesPath.at(0)->getInfo(), "red");
    graphViewer->setVertexColor(nodesPath.at(nodesPath.size() - 1)->getInfo(), "green");
    graphViewer->rearrange();
    sleep(15);

}

template <class T>
void GraphInterface::displayOporto(vector<Edge<T> *> edgesPath) {
    this->graphViewer= new GraphViewer(width, height, false);
    graphViewer->createWindow(this->width, this->height);
    int edgeID = 0;
    for(int eIndex = 0; eIndex < edgesPath.size(); eIndex++) {
        Edge<T>* auxEdge = edgesPath[eIndex];

        graphViewer->addNode(auxEdge->getOrig()->getInfo(), calculateX(auxEdge->getOrig()->getX()), calculateY(auxEdge->getOrig()->getY()));
        graphViewer->addNode(auxEdge->getDest()->getInfo(), calculateX(auxEdge->getDest()->getX()), calculateY(auxEdge->getDest()->getY()));

        if(auxEdge->getOrig()->getVZone() >= 1 && auxEdge->getOrig()->getVZone() <= 6)
            cout << auxEdge->getOrig()->getVZone() << endl ;

        if(auxEdge->getOrig()->getVZone() == ZONE1) {
            graphViewer->setVertexColor(auxEdge->getOrig()->getInfo(), "green");
            graphViewer->setVertexSize(auxEdge->getOrig()->getInfo(), 100);
        }
        else if(auxEdge->getOrig()->getVZone() == ZONE2) {
            graphViewer->setVertexColor(auxEdge->getOrig()->getInfo(), "blue");
            graphViewer->setVertexSize(auxEdge->getOrig()->getInfo(), 100);
        }
        else if(auxEdge->getOrig()->getVZone() == ZONE3) {
            graphViewer->setVertexColor(auxEdge->getOrig()->getInfo(), "red");
            graphViewer->setVertexSize(auxEdge->getOrig()->getInfo(), 100);
        }
        else if(auxEdge->getOrig()->getVZone() == ZONE4) {
            graphViewer->setVertexColor(auxEdge->getOrig()->getInfo(), "black");
            graphViewer->setVertexSize(auxEdge->getOrig()->getInfo(), 100);
        }
        else if(auxEdge->getOrig()->getVZone() == ZONE5) {
            graphViewer->setVertexColor(auxEdge->getOrig()->getInfo(), "cyan");
            graphViewer->setVertexSize(auxEdge->getOrig()->getInfo(), 100);
        }

        if(auxEdge->getDest()->getVZone() == ZONE1) {
            graphViewer->setVertexColor(auxEdge->getDest()->getInfo(), "green");
            graphViewer->setVertexSize(auxEdge->getDest()->getInfo(), 100);
        }
        else if(auxEdge->getDest()->getVZone() == ZONE2) {
            graphViewer->setVertexColor(auxEdge->getDest()->getInfo(), "blue");
            graphViewer->setVertexSize(auxEdge->getDest()->getInfo(), 100);
        }
        else if(auxEdge->getDest()->getVZone() == ZONE3) {
            graphViewer->setVertexColor(auxEdge->getDest()->getInfo(), "red");
            graphViewer->setVertexSize(auxEdge->getDest()->getInfo(), 100);
        }
        else if(auxEdge->getDest()->getVZone() == ZONE4) {
            graphViewer->setVertexColor(auxEdge->getDest()->getInfo(), "black");
            graphViewer->setVertexSize(auxEdge->getDest()->getInfo(), 100);
        }
        else if(auxEdge->getDest()->getVZone() == ZONE5) {
            graphViewer->setVertexColor(auxEdge->getDest()->getInfo(), "cyan");
            graphViewer->setVertexSize(auxEdge->getDest()->getInfo(), 100);
        }

        graphViewer->addEdge(edgeID++, auxEdge->getOrig()->getInfo(), auxEdge->getDest()->getInfo(), EdgeType::DIRECTED);
    }
    graphViewer->rearrange();
}

#endif //FIX_IT_GRAPHINTERFACE_H
