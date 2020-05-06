//
// Created by Tiago on 06/05/2020.
//

#include <iostream>
#include "Task.h"

int Task::current_id = 0;

Task::Task(string function, string localCoords, string beginTime, string endTime) {
    this->function = function;
    this->localCoords = localCoords;
    this->beginTime = beginTime;
    this->endTime = endTime;
    responsiblePicket = nullptr;
    id = current_id++;
}

string Task::getLocalCoords() {
    return localCoords;
}

string Task::getBeginTime() {
    return beginTime;
}

string Task::getEndTime() {
    return endTime;
}

void Task::setLocalCoords(string &localCoords) {
    this->localCoords = localCoords;
}

void Task::setBeginTime(string &beginTime) {
    this->beginTime = beginTime;
}

void Task::setEndTime(string &endTime) {
    this->endTime = endTime;
}

void Task::setResponsiblePicket(Picket *picket) {
    if (function == picket->getRole())
        this->responsiblePicket = picket;
    else
        cerr << "The picket with id " << picket->getId() << " does not have the role " + function;
}

Picket *Task::getResponsiblePicket() {
    return responsiblePicket;
}
