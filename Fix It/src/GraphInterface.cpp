#include "GraphInterface.h"

GraphInterface::GraphInterface(int width, int height, Graph<long>* graph, Company* company) {
    this->width = width;
    this->height = height;
    this->graph = graph;
    this->company = company;

    for(Vertex<long>* vertex: graph->getVertexSet())
        generalFunctions::processCoordinates(vertex->getX(), vertex->getY(), this->minX, this->minY, this->maxX, this->maxY);

//    this->maxX = 535877.2818438777;
//    this->maxY = 4558064.868116516;
//    this->minX = 527178.8739517079;
//    this->minY = 4555491.437477145;
}

double GraphInterface::calculateX(double coord) {
    if ((maxX - minX) == 0)
        return coord * PRECISION;
    else
        return (coord * PRECISION - minX * PRECISION) / ((maxX - minX) * PRECISION / width);
}

double GraphInterface::calculateY(double coord) {
    if ((maxY - minY) == 0)
        return -coord * PRECISION;
    else
        return ((-coord * PRECISION + minY * PRECISION) + (maxY - minY) * PRECISION) /
               ((maxY - minY) * PRECISION / height);
}
