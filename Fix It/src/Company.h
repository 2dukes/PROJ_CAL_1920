//
// Created by Tiago on 12/05/2020.
//

#ifndef FIX_IT_COMPANY_H
#define FIX_IT_COMPANY_H

#include <vector>

#include "Picket.h"
#include "Task.h"

using namespace std;

class Company {
    string name;
    vector<Picket*> pickets;
    vector<Task*> tasks;

public:
    Company(string name);
    string getName();
    bool readPicketsFile(const string& filename);
    bool readTasksFile(const string& filename);
    bool writePicketsFile(const string& filename);
    bool writeTasksFile(const string& filename);
    void addPicket(Picket* picket);
    void addTask(Task* task);
    vector<Picket*> getPickets();
    vector<Task*> getTasks();
};


#endif //FIX_IT_COMPANY_H
