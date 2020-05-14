#include "GraphInterface.h"

GraphInterface::GraphInterface(int width, int height) {
    this->width = width;
    this->height = height;
    this->maxX = 0;
    this->maxY = 0;
    this->minX = 0;
    this->minY = 0;
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
