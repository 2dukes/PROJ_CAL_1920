//
// Created by Tiago on 06/05/2020.
//

#include "Picket.h"

#include <algorithm>

int Picket::current_id = 0;
int Picket::numTasksDone_static = 0;

Picket::Picket(string name, vector<string> roles) {
    this->name = name;
    this->roles = roles;
    id = current_id++;
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

void Picket::setRoles(const vector<string> &role) {
    this->roles = roles;
}

void Picket::addRole(const string &role) {
    roles.push_back(role);
}

bool Picket::removeRole(const string &role) {
    return roles.erase(std::remove(roles.begin(), roles.end(), role), roles.end()) != roles.end();
}

bool Picket::addTask(Task *task) {
    if (task->setResponsiblePicket(this)) {
        tasks.push_back(task);
        numTasksDone = ++numTasksDone_static;
        return true;
    }
    return false;
}

vector<Task*> Picket::getTasks() {
    return tasks;
}

int Picket::getNumTasksDone() {
    return numTasksDone;
}



