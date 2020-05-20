#ifndef FIX_IT_PAIRING_H
#define FIX_IT_PAIRING_H

#include "TSP.h"
#include "Picket.h"
#include "Task.h"

using namespace std;

class Pairing {

    vector<Task*> tasks;
    vector<Picket*> pickets;
    int maxZone;

    vector<vector<Task*>> tasksByZone;

    void setMaxZone();

    void divideTasksByZone();


public:
    Pairing(vector<Task*> tasks, vector<Picket*> pickets);
    vector<vector<Task*>> getTasksByZone();
    void setTasksToPickets();
};

Pairing::Pairing(vector<Task *> tasks, vector<Picket *> pickets) {
    this->tasks = tasks;
    this->pickets = pickets;
    setMaxZone();
    divideTasksByZone();
}

void Pairing::setMaxZone() {
    maxZone = ZONE0;
    for (auto task: tasks) {
        maxZone = max(task->getZone(), maxZone);
    }
    vector<Task*> v;
    for (int i = 0; i < maxZone; i++) {
        tasksByZone.push_back(v);
    }
}

void Pairing::divideTasksByZone() {
    for (auto task: tasks) {
        tasksByZone.at(task->getZone()-1).push_back(task);
    }
}

vector<vector<Task *>> Pairing::getTasksByZone() {
    return tasksByZone;
}

void Pairing::setTasksToPickets() {
    for (int i = 0; i < tasksByZone.size(); i++) {
        for (int j = 0; j < tasksByZone.at(i).size(); j++) {
            
        }
    }
}

#endif //FIX_IT_PAIRING_H
