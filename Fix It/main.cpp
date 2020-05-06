#include <cstdio>
#include "src/GraphViewer/graphviewer.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "src/Picket.h"
#include "src/Task.h"

int main() {

    vector<string> roles;
    roles.push_back("Eletricista");
    roles.push_back("Canalisador");

    Picket* picket = new Picket("Ze", roles);

    Task* task1 = new Task("Eletricista", "12.214, 13.214", "12:30", "15:30");
    Task* task2 = new Task("Canalisador", "13.214, 14.214", "16:30", "18:30");

    picket->addTask(task1);
    picket->addTask(task2);

    cout << "Num tasks done: " << to_string(picket->getNumTasksDone()) << endl;




    return 0;
}
