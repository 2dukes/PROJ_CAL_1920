//
// Created by Tiago on 06/05/2020.
//

#ifndef FIX_IT_TASK_H
#define FIX_IT_TASK_H

#include <string>
#include "Picket.h"

using namespace std;

class Picket;

class Task {
    static int current_id;
    int id;
    string function;
    Picket* responsiblePicket;
    string localCoords; // mudar para classe Coord ?...
    string beginTime;
    string endTime; // mudar para classe Time

public:
    Task(string function, string localCoords, string beginTime, string endTime);
    string getLocalCoords();
    string getBeginTime();
    string getEndTime();
    void setLocalCoords(const string &localCoords);
    void setBeginTime(const string &beginTime);
    void setEndTime(const string &endTime);
    bool setResponsiblePicket(Picket *picket);
    Picket* getResponsiblePicket();
    bool isDone();
};


#endif //FIX_IT_TASK_H
