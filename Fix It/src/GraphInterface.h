#ifndef FIX_IT_GRAPHINTERFACE_H
#define FIX_IT_GRAPHINTERFACE_H

#include "Graph/Graph.h"
#include "GraphViewer/graphviewer.h"

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
};

template <class T>
void GraphInterface::displayPath(vector<Vertex<T> *> nodesPath) {
    /*this->gv = new GraphViewer(width, height, false);
    // gv->setBackground(MAP_BACKGROUND);
    gv->createWindow(this->width, this->height);

    for (Edge *edge: path) {
        Vertex *ori = edge->getOrig();
        this->gv->addNode(ori->getInfo().getId(),
                          calculateX(ori->getInfo().getX()),
                          calculateY(ori->getInfo().getY())
        );
        Vertex *dest = edge->getDest();
        this->gv->addNode(dest->getInfo().getId(),
                          calculateX(ori->getInfo().getX()),
                          calculateY(ori->getInfo().getY())
        );
        // TODO: Hashing the ID's?
        this->gv->addEdge(this->getEdgeId(),
                          ori->getInfo().getId(),
                          dest->getInfo().getId(),
                          EdgeType::DIRECTED);


        if (ori->isStartPoint()) {
            this->gv->setVertexColor(ori->getInfo().getId(), WHITE);
        }
        if (dest->isEndPoint()) {
            this->gv->setVertexColor(dest->getInfo().getId(), BLACK);
        }
        if (ori->isMiddlePoint()) {
            this->gv->setVertexColor(ori->getInfo().getId(), RED);
        }
        if (dest->isMiddlePoint()) {
            this->gv->setVertexColor(dest->getInfo().getId(), RED);
        }

        if (edge->isBus()) {
            if(!ori->isCheckpoint())
                this->gv->setVertexColor(ori->getInfo().getId(), BLUE);
            if(!dest->isCheckpoint())
                this->gv->setVertexColor(dest->getInfo().getId(), BLUE);
            this->gv->setEdgeColor(this->getEdgeId(), BLUE);
        } else if (edge->isSubway()) {
            if(!ori->isCheckpoint())
                this->gv->setVertexColor(ori->getInfo().getId(), YELLOW);
            if(!dest->isCheckpoint())
                this->gv->setVertexColor(dest->getInfo().getId(), YELLOW);
            this->gv->setEdgeColor(this->getEdgeId(), YELLOW);
        } else {
            if(!ori->isCheckpoint())
                this->gv->setVertexColor(ori->getInfo().getId(), GREEN);
            if(!dest->isCheckpoint())
                this->gv->setVertexColor(dest->getInfo().getId(), GREEN);
            this->gv->setEdgeColor(this->getEdgeId(), GREEN);
        }

        this->gv->rearrange();
        this->incrementEdgeId();
        //sleep(1);
    }*/
}

#endif //FIX_IT_GRAPHINTERFACE_H
