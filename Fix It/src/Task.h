//
// Created by Tiago on 06/05/2020.
//

#ifndef FIX_IT_TASK_H
#define FIX_IT_TASK_H

#include <string>
#include "Picket.h"
#include "Utils/Time.h"

using namespace std;

class Time;

class Picket;


class Task {
    static int current_id;
    int id;
    string function;
    Picket* responsiblePicket;
    string localCoords; // mudar para classe Coord ?...
    Time beginTime;
    Time endTime;

public:
    Task(string function, string localCoords, Time beginTime, Time endTime);
    string getLocalCoords() const;
    Time getBeginTime() const;
    Time getEndTime() const;
    void setLocalCoords(const string &localCoords);
    void setBeginTime(Time &beginTime);
    void setEndTime(Time &endTime);
    bool setResponsiblePicket(Picket *picket);
    Picket* getResponsiblePicket() const;
    bool isDone() const;
};


#endif //FIX_IT_TASK_H
