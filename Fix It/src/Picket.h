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
    vector<string> roles;
    vector<Task*> tasks;
    static int numTasksDone_static;
    int numTasksDone;

public:
    Picket(string name, vector<string> roles);
    int getId();
    string getName();
    vector<string> getRoles();
    void setName(const string &name);
    void setRoles(const vector<string> &roles);
    void addRole(const string &role);
    bool removeRole(const string &role); // true se removeu, false se não existia
    bool addTask(Task *task);
    vector<Task*> getTasks();
    int getNumTasksDone();
};


#endif //FIX_IT_PICKET_H
