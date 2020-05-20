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
    void displayOporto(vector<Edge<T> *> edgesPath, vector<Vertex<T>*> vertexes);
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
        graphViewer->addNode(auxVertex->getInfo(), auxVertex->getX(), auxVertex->getY());
        graphViewer->addNode(nextAuxVertex->getInfo(), nextAuxVertex->getX(), nextAuxVertex->getY());
        graphViewer->addEdge(edgeID++, auxVertex->getInfo(), nextAuxVertex->getInfo(), EdgeType::DIRECTED);
    }
    graphViewer->setVertexColor(nodesPath.at(0)->getInfo(), "red");
    graphViewer->setVertexColor(nodesPath.at(nodesPath.size() - 1)->getInfo(), "green");
    graphViewer->rearrange();
    sleep(15);

}

template <class T>
void GraphInterface::displayOporto(vector<Edge<T> *> edgesPath, vector<Vertex<T>* > vertexes) {
    this->graphViewer= new GraphViewer(width, height, false);
    graphViewer->createWindow(this->width, this->height);
    int edgeID = 0;
    for(auto v: vertexes) {
        if(v->getInfo() == 1)
            graphViewer->setVertexColor(v->getInfo(), "green");
        if(v->getInfo() == 287)
            graphViewer->setVertexColor(v->getInfo(), "red");
        graphViewer->addNode(v->getInfo(), v->getX(), v->getY());

//        if(v->getVZone() >= 1 && v->getVZone() <= 3) {
//            cout << v->getInfo() << endl;
//        }
        if(v->getVZone() == ZONE1) {
            graphViewer->setVertexColor(v->getInfo(), "green");
            graphViewer->setVertexSize(v->getInfo(), 100);
        }
        else if(v->getVZone() == ZONE2) {
            graphViewer->setVertexColor(v->getInfo(), "blue");
            graphViewer->setVertexSize(v->getInfo(), 100);
        }
        else if(v->getVZone() == ZONE3) {
            graphViewer->setVertexColor(v->getInfo(), "red");
            graphViewer->setVertexSize(v->getInfo(), 100);
        }
        else if(v->getVZone() == ZONE4) {
            graphViewer->setVertexColor(v->getInfo(), "black");
            graphViewer->setVertexSize(v->getInfo(), 100);
        }
    }

    for(int eIndex = 0; eIndex < edgesPath.size(); eIndex++) {
        Edge<T>* auxEdge = edgesPath[eIndex];
        graphViewer->addEdge(edgeID++, auxEdge->getOrig()->getInfo(), auxEdge->getDest()->getInfo(), EdgeType::DIRECTED);
    }
    graphViewer->rearrange();
}

#endif //FIX_IT_GRAPHINTERFACE_H
