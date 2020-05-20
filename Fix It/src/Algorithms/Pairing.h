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
    Graph<long>* graph;
    long startVertexId;

    vector<vector<Task*>> tasksByZone;

    void setMaxZone();

    void divideTasksByZone();

    void setZonesToPickets();

    Task* getTaskById(long vertexId);


public:
    Pairing(vector<Task*> tasks, vector<Picket*> pickets, Time beginTime, Time endTime, Graph<long>* graph, long startVertexId);
    vector<vector<Task*>> getTasksByZone();
    void setTasksToPickets();
};

Pairing::Pairing(vector<Task *> tasks, vector<Picket *> pickets, Time beginTime, Time endTime, Graph<long>* graph, long startVertexId) {
    this->tasks = tasks;
    this->pickets = pickets;
    this->beginTime = beginTime;
    this->endTime = endTime;
    this->graph = graph;
    this->startVertexId = startVertexId;
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

vector<vector<Task *>> Pairing::getTasksByZone() {
    return tasksByZone;
}

void Pairing::setTasksToPickets() {
//    for (int i = 0; i < tasksByZone.size(); i++) {
//        for (int j = 0; j < tasksByZone.at(i).size(); j++) {
//
//        }
//    }

    for (int zone = 0; zone < maxZone; zone++) {
        vector<Task*> tasksToPair = tasksByZone.at(zone);
        vector<long> tasksIds;
        for (auto task: tasksToPair) {
            tasksIds.push_back(task->getNodeId());
        }
        TSP<long> tsp(graph);
        vector<long> path = tsp.calculatePath(tasksIds, startVertexId, startVertexId); // começa e acaba no início

        Time currentTime = beginTime;
        for (auto idVertex: path) {
            if (generalFunctions::inVector<long>(tasksIds, idVertex)) { // se o ponto atual do path for o ponto de uma task
                Task* task = getTaskById(idVertex);
                string function = task->getFunction();
                for (auto picket: pickets) {
                    if (picket->verifyRole(function) && picket->getZone() == zone) {
                        //cout << "The picket with id " << picket->getId() << " will complete the task with id " << idVertex << endl;
                        picket->addTask(task);
                        cout << "  PICKET:" << endl;
                        cout << "Id: " << picket->getId() << endl;
                        vector<string> roles = picket->getRoles();
                        cout << "Roles: " << generalFunctions::coutVectorString(roles) << endl;
                        cout << "  Task: " << endl;
                        cout << "Id: " << function << endl;
                        cout << "Zone: " << zone << endl;
                        cout << "--------------------\n";
                        break;
                    }
                }
            }
        }
    }

}

Task *Pairing::getTaskById(long vertexId) {
    for (auto task: tasks) {
        if (task->getNodeId() == vertexId)
            return task;
    }
    return nullptr; // nunca chega aqui
}

void Pairing::setZonesToPickets() { // divide os piquetes pelas zonas de forma aleatória; mudar isso depois
    int num;
    for (auto picket: pickets) {
        num = rand() % maxZone;
        picket->setZone(num);
    }
}

#endif //FIX_IT_PAIRING_H
