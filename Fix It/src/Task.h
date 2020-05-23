//
// Created by Tiago on 06/05/2020.
//

#ifndef FIX_IT_TASK_H
#define FIX_IT_TASK_H

#include <string>
#include "Picket.h"
#include "Utils/Time.h"
#include "Graph/Graph.h"
#include <string>


using namespace std;

class Time;

class Picket;


class Task {
    static int current_id;      // ID da última task inserida

    int id;                     // Task ID

    string function;            // Função requerida para realizar a task

    Picket* responsiblePicket;  // Picket responsável por fazer a task

    long int nodeId;            // ID do nó correspondente

    int durationMinutes;        // Duração em minutos

    Time beginTime;             // Tempo de início

    MAP_ZONE zone;              // Zona do mapa a que a task pertence

public:
    Task(string function, long int nodeId, int durationMinutes);
    long int getNodeId() const;
    void setNodeId(long nodeId);
    string getFunction() const;
    int getDurationMinutes() const;
    Time getBeginTime() const;
    Time getEndTime() const;
    void setBeginTime(Time &beginTime);
    bool setResponsiblePicket(Picket *picket);
    Picket* getResponsiblePicket() const;
    bool hasPicket() const;
    bool hasDefinedTime() const;
    friend ostream& operator<<(ostream& os, const Task &task);
    void setZone(MAP_ZONE zone);
    int getZone() const;
    void removeResponsiblePicket();
};


#endif //FIX_IT_TASK_H
