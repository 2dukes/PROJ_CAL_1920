
#ifndef FIX_IT_NECESSARYFUNCTIONS_NAMESPACES_H
#define FIX_IT_NECESSARYFUNCTIONS_NAMESPACES_H

#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <Task.h>
#include "../Graph/Graph.h"

namespace verifyInputs {
    bool verifyString(std::string auxStr);
    bool verifyNumber();
}

namespace readOperations {
    std::string readString(std::string parameter);
    std::string readRole(std::string parameter);
    std::vector<std::string> readVectorString(std::string parameter);
    std::string confirmAnswer();

    template <class T>
    T readNumber(std::string parameter)
    {
        T auxNum;
        do {
            std::cout << parameter;
            std::cin >> auxNum;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while(verifyInputs::verifyNumber());
        return auxNum;
    }
}

namespace generalFunctions {
    std::string coutVectorString(const std::vector<std::string> &v);
    void trim(std::string &str);
    std::vector<std::string> separate_string(std::string str, char separator);

    template <class T>
    bool inVector(std::vector<T> v, T elem) {
        for (auto &x: v) {
            if (x == elem)
                return true;
        }
        return false;
    }

    template <class T>
    double heuristicDistance(Vertex<T> *origin, Vertex<T> *dest) {
        return sqrt(pow(origin->getX() - dest->getX(), 2) + pow(origin->getY() - dest->getY(), 2));
    }

    void processCoordinates(double x, double y, double &minX, double &minY, double &maxX, double &maxY);

    Task *getTaskById(long vertexId, const vector<Task*> &tasks);

}





#endif //FIX_IT_NECESSARYFUNCTIONS_NAMESPACES_H
