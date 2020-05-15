#include "GraphInterface.h"

GraphInterface::GraphInterface(int width, int height) {
    this->width = width;
    this->height = height;
    this->maxX = 535877.2818438777 ;
    this->maxY = 4558064.868116516;
    this->minX = 527178.8739517079;
    this->minY = 4555491.437477145;
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
