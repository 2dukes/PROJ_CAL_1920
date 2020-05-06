//
// Created by Tiago on 06/05/2020.
//

#include <iostream>
#include "Task.h"

#include <algorithm>

int Task::current_id = 0;

Task::Task(string function, string localCoords, Time beginTime, Time endTime) {
    this->function = function;
    this->localCoords = localCoords;
    this->beginTime = beginTime;
    this->endTime = endTime;
    responsiblePicket = nullptr;
    id = current_id++;
}

string Task::getLocalCoords() const {
    return localCoords;
}

Time Task::getBeginTime() const {
    return beginTime;
}

Time Task::getEndTime() const {
    return endTime;
}

void Task::setLocalCoords(const string &localCoords) {
    this->localCoords = localCoords;
}

void Task::setBeginTime(Time &beginTime) {
    this->beginTime = beginTime;
}

void Task::setEndTime(Time &endTime) {
    this->endTime = endTime;
}

bool Task::setResponsiblePicket(Picket *picket) {
    if (isDone()) {
        cerr << "This task is already attributed to the picket with id " + to_string(this->responsiblePicket->getId()) << endl;
        return false;
    }
    vector<string> roles = picket->getRoles();
    if (std::find(roles.begin(), roles.end(), function) != roles.end()) {
        this->responsiblePicket = picket;
        return true;
    }
    else {
        cerr << "The picket with id " << picket->getId() << " does not have the role " + function << endl;
        return false;
    }

}

Picket *Task::getResponsiblePicket() const {
    return responsiblePicket;
}

bool Task::isDone() const {
    return responsiblePicket != nullptr;
}
