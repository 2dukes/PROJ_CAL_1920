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

//    Time currentTime = beginTime;
    for (int zone = 1; zone <= maxZone; zone++) {
        vector<Task*> tasksToPair = tasksByZone.at(zone-1);
        vector<long> tasksIds;
        for (auto task: tasksToPair) {
            tasksIds.push_back(task->getNodeId());
        }
        TSP<long> tsp(graph);
        vector<long> path = tsp.calculatePath(tasksIds, startVertexId, startVertexId); // começa e acaba no início

//        currentTime = beginTime;
        for (auto idVertex: path) {
//            if (endTime < currentTime || endTime == currentTime) {
//                cerr << "Nao foi possivel atribuir as tarefas todas (o tempo nao chegou)\n";
//                break;
//            }
            if (generalFunctions::inVector<long>(tasksIds, idVertex)) { // se o ponto atual do path for o ponto de uma task
                Task* task = getTaskById(idVertex);
                string function = task->getFunction();

                if (task->hasPicket()) {
                    continue;
                }
//                Time timeCopy = currentTime;
                for (auto picket: pickets) {

                    if ((endTime < picket->getCurrentTime().addMinutes(task->getDurationMinutes()+1)) || (picket->getCurrentTime().addMinutes(task->getDurationMinutes()+1) == endTime)) {
                        //currentTime = beginTime;
//                        currentTime = beginTime;
                        continue;
                    }

                    if (!picket->timeIsCompatible(picket->getCurrentTime(), picket->getCurrentTime().addMinutes(task->getDurationMinutes()))) {
//                        currentTime = beginTime;
                        continue;
                    }
                    if (!picket->getZone() == zone) {
//                        currentTime = timeCopy;
                        continue;
                    }
                    if (!picket->verifyRole(function)) {
//                        currentTime = timeCopy;
                        continue;
                    }
                    Time currentTime = picket->getCurrentTime();
                    task->setBeginTime(currentTime);
//                    currentTime = currentTime.addMinutes(task->getDurationMinutes()+1); // 1 minuto entre cada task; mudar dps
                    picket->addTask(task);
                    break;

                }
            }
        }
        for (auto task: tasksToPair) {
            if (!task->hasPicket()) {
                cerr << "There is no picket compatible with the task with id " << task->getNodeId() << endl;
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
        num = rand() % (maxZone) + 1;
        picket->setZone(num);
        picket->setInitTime(beginTime);
    }
}

#endif //FIX_IT_PAIRING_H
