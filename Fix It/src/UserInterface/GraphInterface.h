#ifndef FIX_IT_GRAPHINTERFACE_H
#define FIX_IT_GRAPHINTERFACE_H

#include "Graph/Graph.h"
#include "Algorithms/TSP.h"
#include "../../lib/graphviewer.h"
#include "Company.h"
#include <unistd.h>
#include <sstream>

#define PRECISION 10e9

class GraphInterface {
    GraphViewer *graphViewer;
    Graph<long>* graph;
    Company* company;
    int width;
    int height;
    double maxX;
    double maxY;
    double minX;
    double minY;

    double calculateX(double coord);
    double calculateY(double coord);

public:
    GraphInterface(int width, int height, Graph<long>* graph, Company* company);

    template <class T>
    void displayPath(vector<Edge<T> *> edgesPath, vector<Vertex<T>* > vertexes, vector<T> pathToCalc, vector<T> tasks, T companyPlaceID);

    template<class T>
    void displayOporto(vector<Edge<T> *> edgesPath, vector<Vertex<T>*> vertexes,  T companyPlaceID);
};

template <class T>
void GraphInterface::displayPath(vector<Edge<T> *> edgesPath, vector<Vertex<T>* > vertexes, vector<T> pathToCalc, vector<T> tasks, T companyPlaceID) {

    this->graphViewer= new GraphViewer(width, height, false);
    // graphViewer->setBackground(MAP_BACKGROUND);
    graphViewer->createWindow(this->width, this->height);

    int edgeID = 0;

    // Entire MAP
    for(auto v: vertexes)
        graphViewer->addNode(v->getInfo(), v->getX(), v->getY());

    for(int eIndex = 0; eIndex < edgesPath.size(); eIndex++) {
        Edge<T>* auxEdge = edgesPath[eIndex];
        bool flag = false;

        for(int vIndex = 0; vIndex < pathToCalc.size() - 2; vIndex++) {
            if(pathToCalc[vIndex] == auxEdge->getOrig()->getInfo() && pathToCalc[vIndex + 1] == auxEdge->getDest()->getInfo()) {
                flag = true;
                break;
            }
        }
        if(flag) {
            graphViewer->addEdge(edgeID++, auxEdge->getOrig()->getInfo(), auxEdge->getDest()->getInfo(), EdgeType::DIRECTED);
            graphViewer->setEdgeColor(edgeID - 1, "black");
            graphViewer->setEdgeThickness(edgeID - 1, 10);
        }
        else
            graphViewer->addEdge(edgeID++, auxEdge->getOrig()->getInfo(), auxEdge->getDest()->getInfo(), EdgeType::DIRECTED);

    }

    for(int vIndex = 0; vIndex < pathToCalc.size() - 1; vIndex++)
        graphViewer->setVertexColor(pathToCalc[vIndex], "gray");


    for(auto taskID: tasks) {
        for(auto task: company->getTasks()) {
            if(task->getNodeId() == taskID) {
                if(!(task->getBeginTime() == Time(0, 0))) {
                    ostringstream o_stream;
                    o_stream << "Begin Time: " << task->getBeginTime() << " | "
                             << "End Time:" << task->getEndTime() << " | "
                             << "Task Node ID: " << taskID << endl;
                    graphViewer->setVertexLabel(taskID, o_stream.str());
                }
                break;
            }
        }

        if(graph->findVertex(taskID)->getVZone() == 1)
            graphViewer->setVertexColor(taskID, "green");
        else if(graph->findVertex(taskID)->getVZone() == 2)
            graphViewer->setVertexColor(taskID, "blue");
        else if(graph->findVertex(taskID)->getVZone() == 3)
            graphViewer->setVertexColor(taskID, "red");
        else if(graph->findVertex(taskID)->getVZone() == 4)
            graphViewer->setVertexColor(taskID, "black");

        graphViewer->setVertexSize(taskID, 75);
    }

    graphViewer->setVertexColor(companyPlaceID, "cyan");
    graphViewer->setVertexSize(companyPlaceID, 125);
    graphViewer->setVertexLabel(companyPlaceID, "Sede FIX IT");

    graphViewer->rearrange();

}

template <class T>
void GraphInterface::displayOporto(vector<Edge<T> *> edgesPath, vector<Vertex<T>* > vertexes, T companyPlaceID) {
    this->graphViewer= new GraphViewer(width, height, false);
    graphViewer->createWindow(this->width, this->height);
    int edgeID = 0;
    for(auto v: vertexes) {
        graphViewer->addNode(v->getInfo(), v->getX(), v->getY());

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

    graphViewer->setVertexColor(companyPlaceID, "cyan");
    graphViewer->setVertexSize(companyPlaceID, 125);
    graphViewer->setVertexLabel(companyPlaceID, "Sede FIX IT");

    graphViewer->rearrange();
}

#endif //FIX_IT_GRAPHINTERFACE_H
