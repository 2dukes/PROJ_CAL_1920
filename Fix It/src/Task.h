//
// Created by Tiago on 06/05/2020.
//

#ifndef FIX_IT_TASK_H
#define FIX_IT_TASK_H

#include <string>
#include "Picket.h"
#include "Utils/Time.h"
#include "Graph/Graph.h"

using namespace std;

class Time;

class Picket;


class Task {
    static int current_id;
    int id;
    string function;
    Picket* responsiblePicket;
    long int nodeId;
    int durationMinutes;
    Time beginTime;

public:
    Task(string function, long int nodeId, int durationMinutes);
    long int getNodeId() const;
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
};


#endif //FIX_IT_TASK_H
