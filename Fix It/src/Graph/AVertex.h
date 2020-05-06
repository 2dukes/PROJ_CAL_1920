//
// Created by Rui Pinto on 5/6/2020.
//

#ifndef FIX_IT_AVERTEX_H
#define FIX_IT_AVERTEX_H

#include "../Graph/Graph.h"

template <class T>
class AVertex : public Vertex<T> {
    double gScore;                 // required by A* Algorithm

public:
    AVertex(T in);
    bool operator<(AVertex<T> & vertex) const; // required by A* algorithm... Different from the original operator<
                                               // That's why we created this new derived class.
};

template <class T>
AVertex<T>::AVertex(T in): Vertex<T>(in), gScore(0.0) { }

template <class T>
bool AVertex<T>::operator<(AVertex<T> &vertex) const {
    return this->gScore < vertex.gScore;
}

#endif //FIX_IT_AVERTEX_H
