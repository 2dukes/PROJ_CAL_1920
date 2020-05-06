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
    void setLocalCoords(string &localCoords);
    void setBeginTime(string &beginTime);
    void setEndTime(string &endTime);
    void setResponsiblePicket(Picket *picket);
    Picket* getResponsiblePicket();
};


#endif //FIX_IT_TASK_H
