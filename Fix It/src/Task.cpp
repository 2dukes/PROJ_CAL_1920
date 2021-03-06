//
// Created by Tiago on 06/05/2020.
//

#include <iostream>
#include "Task.h"

#include <algorithm>
#include <sstream>

int Task::current_id = 0;

Task::Task(string function, long int nodeId, int durationMinutes) {
    this->function = function;
    this->nodeId = nodeId;
    this->durationMinutes = durationMinutes;
    this->beginTime = Time(0, 0);
    responsiblePicket = nullptr;
    id = current_id++;
}

long int Task::getNodeId() const {
    return nodeId;
}

string Task::getFunction() const {
    return function;
}

int Task::getDurationMinutes() const {
    return durationMinutes;
}

Time Task::getBeginTime() const {
    return beginTime;
}

Time Task::getEndTime() const {
    return beginTime.addMinutes(durationMinutes);
}

void Task::setBeginTime(Time &beginTime) {
    this->beginTime = beginTime;
}

bool Task::setResponsiblePicket(Picket *picket) {
    if (hasPicket()) {
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

bool Task::hasPicket() const {
    return responsiblePicket != nullptr;
}

bool Task::hasDefinedTime() const {
    return !(beginTime == Time(0, 0));
}

ostream &operator<<(ostream &os, const Task &task) {
    if(os.rdbuf() == std::cout.rdbuf()) {
        os << "Function: " << task.getFunction() << endl;
        os << "NodeId: " << task.getNodeId() << endl;
        os << "Duration: " << task.getDurationMinutes() << endl;

        if(!(task.getBeginTime() == Time(0, 0)) && task.hasPicket()) {
            os << "Begin Time: " << task.getBeginTime() << endl;
            os << "End Time: " << task.getBeginTime().addMinutes(task.getDurationMinutes()) << endl;
            os << "Responsible Picket: " << task.getResponsiblePicket()->getId() << endl;
        }
    }
    else {
        os << "Function: " << task.getFunction() << endl;
        os << "NodeId: " << task.getNodeId() << endl;
        os << "Duration: " << task.getDurationMinutes() << endl;
    }

    return os;
}

void Task::setZone(MAP_ZONE zone) {
    this->zone = zone;
}

int Task::getZone() const {
    return zone;
}

void Task::setNodeId(long nodeId) {
    this->nodeId = nodeId;
}

void Task::removeResponsiblePicket() {
    responsiblePicket = nullptr;
}



