//
// Created by Tiago on 06/05/2020.
//

#ifndef FIX_IT_PICKET_H
#define FIX_IT_PICKET_H

#include <string>
#include <vector>
#include "Task.h"

using namespace std;

class Task;

class Picket {
    static int current_id;
    int id;
    string name;
    string role;
    vector<Task*> tasks;

public:
    Picket(string name, string role);
    int getId();
    string getName();
    string getRole();
    void setName(string &name);
    void setRole(string &role);
    void addTask(Task *task);
    vector<Task*> getTasks();
};


#endif //FIX_IT_PICKET_H
