//
// Created by Tiago on 06/05/2020.
//

#include "Picket.h"

int Picket::current_id = 0;

Picket::Picket(string name, string role) {
    this->name = name;
    this->role = role;
    id = current_id++;
}

int Picket::getId() {
    return id;
}

string Picket::getName() {
    return name;
}

string Picket::getRole() {
    return role;
}

void Picket::setName(string &name) {
    this->name = name;
}

void Picket::setRole(string &role) {
    this->role = role;
}

