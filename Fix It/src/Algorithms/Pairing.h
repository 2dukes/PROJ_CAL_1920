#ifndef FIX_IT_PAIRING_H
#define FIX_IT_PAIRING_H

#include "TSP.h"
#include "Picket.h"
#include "Task.h"
#include "Utils/NecessaryFunctions_NameSpaces.h"

#include <vector>

using namespace std;

class Pairing {

    vector<Task*> tasks;
    vector<Picket*> pickets;
    int maxZone;
    Time beginTime;
    Time endTime;

    vector<vector<Task*>> tasksByZone;
    void setMaxZone();
    void divideTasksByZone();
    void setZonesToPickets();
    Task* getTaskById(long vertexId);


public:
    Pairing(vector<Task*> tasks, vector<Picket*> pickets, Time beginTime, Time endTime);
    void setTasksToPickets();
};

Pairing::Pairing(vector<Task *> tasks, vector<Picket *> pickets, Time beginTime, Time endTime) {
    this->tasks = tasks;
    this->pickets = pickets;
    this->beginTime = beginTime;
    this->endTime = endTime;
    setMaxZone();
    divideTasksByZone();
    setZonesToPickets();
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

Task *Pairing::getTaskById(long vertexId) {
    for (auto task: tasks) {
        if (task->getNodeId() == vertexId)
            return task;
    }
    return nullptr; // nunca chega aqui
}

void Pairing::setZonesToPickets() { // divide os piquetes pelas zonas de forma aleatória
    int num;
    for (auto picket: pickets) {
        num = rand() % maxZone + 1;
        picket->setZone(num);
        picket->setCurrentTime(beginTime);
    }
}

void Pairing::setTasksToPickets() {
    for (int zone = 1; zone <= maxZone; zone++) {
        vector<Task*> tasksToPair = tasksByZone.at(zone-1);
        vector<long> tasksIds;
        for (auto task: tasksToPair) {
            tasksIds.push_back(task->getNodeId());
        }

        for (auto idVertex: tasksIds) {

            Task* task = getTaskById(idVertex);
            string function = task->getFunction();

            if (task->hasPicket()) {
                continue;
            }

            for (auto picket: pickets) {

                if (picket->getZone() != task->getZone() || !picket->verifyRole(function)) {
                    continue;
                }

                if ((endTime < picket->getCurrentTime().addMinutes(task->getDurationMinutes()+1)) || (picket->getCurrentTime().addMinutes(task->getDurationMinutes()+1) == endTime)) {
                    continue;
                }

                if (!picket->timeIsCompatible(picket->getCurrentTime(), picket->getCurrentTime().addMinutes(task->getDurationMinutes()))) {
                    continue;
                }

                Time currentTime = picket->getCurrentTime();
                task->setBeginTime(currentTime);
                picket->addTask(task);
                break;
            }
        }

        for (auto task: tasksToPair) {
            if (!task->hasPicket()) {
                cerr << "There is no picket compatible with the task with id " << task->getNodeId() << endl;
            }
        }

    }
}

#endif //FIX_IT_PAIRING_H
