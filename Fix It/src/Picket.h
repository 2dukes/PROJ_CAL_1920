//
// Created by Tiago on 06/05/2020.
//

#ifndef FIX_IT_PICKET_H
#define FIX_IT_PICKET_H

#include <string>
#include <vector>
#include "Task.h"
#include "Utils/Time.h"

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
    bool timeIsCompatible(const Time &time1, const Time &time2) const;

public:
    Picket(string name, vector<string> roles, int numTasksDone);
    int getId() const;
    string getName() const;
    vector<string> getRoles() const;
    void setName(const string &name);
    void setRoles(const vector<string> &roles);
    void addRole(const string &role);
    bool removeRole(const string &role); // true se removeu, false se não existia
    bool addTask(Task *task);
    vector<Task*> getTasks() const;
    int getNumTasksDone() const;
};


#endif //FIX_IT_PICKET_H
