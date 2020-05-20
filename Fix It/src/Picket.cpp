//
// Created by Tiago on 06/05/2020.
//

#include "Picket.h"
#include "Utils/NecessaryFunctions_NameSpaces.h"

#include <algorithm>
#include <iostream>

int Picket::current_id = 0;

Picket::Picket(string name, vector<string> roles, int numTasksDone) {
    this->name = name;
    this->roles = roles;
    this->numTasksDone = numTasksDone;
    id = current_id++;
    zone = -1;
}

int Picket::getId() const {
    return id;
}

string Picket::getName() const {
    return name;
}

vector<string> Picket::getRoles() const {
    return roles;
}

void Picket::setName(const string &name) {
    this->name = name;
}

void Picket::setRoles(const vector<string> &roles) {
    this->roles = roles;
}

void Picket::addRole(const string &role) {
    roles.push_back(role);
}

bool Picket::removeRole(const string &role) {
    return roles.erase(std::remove(roles.begin(), roles.end(), role), roles.end()) != roles.end();
}

bool Picket::addTask(Task *task) {
    if (!timeIsCompatible(task->getBeginTime(), task->getEndTime())) {
        cerr << "The task time is not compatible with the tasks of the picket" << endl;
        return false;
    }
    if (task->setResponsiblePicket(this)) {
        tasks.push_back(task);
        numTasksDone++;
        return true;
    }
    return false;
}

vector<Task*> Picket::getTasks() const {
    return tasks;
}

int Picket::getNumTasksDone() const {
    return numTasksDone;
}

bool Picket::timeIsCompatible(const Time &time1, const Time &time2) const {
    for (auto task : tasks) {
        if (time1.checkTimeOverlap(task->getBeginTime(), task->getEndTime()))
            return false;
        if (time2.checkTimeOverlap(task->getBeginTime(), task->getEndTime()))
            return false;
    }
    return true;
}

ostream &operator<<(ostream &os, const Picket &picket) {
    os << "Name: " << picket.getName() << endl;
    os << "Roles: " << generalFunctions::coutVectorString(picket.getRoles()) << endl;
    os << "Tasks Done: " << picket.getNumTasksDone() << endl;
    return os;
}

bool Picket::verifyRole(const string &role) const {
    for (auto r: roles) {
        if (r == role)
            return true;
    }
    return false;
}

void Picket::setZone(int zone) {
    this->zone = zone;
}

int Picket::getZone() const {
    return zone;
}



