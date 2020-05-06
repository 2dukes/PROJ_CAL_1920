#include <cstdio>
#include "src/GraphViewer/graphviewer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Utils/Time.h>

using namespace std;

#include "src/Picket.h"
#include "src/Task.h"

int main() {

    Time beginTime("23:56");
    Time endTime("0:10");

    vector<string> roles;
    roles.push_back("Eletricista");
    roles.push_back("Canalisador");

    Picket* picket = new Picket("Ze", roles);

    Task* task1 = new Task("Eletricista", "12.214, 13.214", beginTime, endTime);
    Task* task2 = new Task("Canalisador", "13.214, 14.214", beginTime, endTime);

    picket->addTask(task1);
    picket->addTask(task2);

    cout << "Num tasks done: " << to_string(picket->getNumTasksDone()) << endl;


    Time time = beginTime.getTimeInterval(endTime);

    cout << "Hours: " + to_string(time.getHours()) << endl;
    cout << "Minutes: " + to_string(time.getMinutes()) << endl;






    return 0;
}
