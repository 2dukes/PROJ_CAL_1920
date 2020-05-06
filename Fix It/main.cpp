#include <cstdio>
#include "src/GraphViewer/graphviewer.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "src/Picket.h"
#include "src/Task.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Picket* picket = new Picket("Ze", "Eletricista");

    Task* task = new Task("Eletricista", "12.214, 13.214", "12:30", "15:30");

    picket->addTask(task);



    //task.setResponsiblePicket(picket);

    cout << "The picket for the task with coords " + task->getLocalCoords() + " and with begin time at "
        + task->getBeginTime() + " and end time at " + task->getEndTime() + " is picket with id = "
        + to_string(task->getResponsiblePicket()->getId()) + ", his name is " + task->getResponsiblePicket()->getName()
        + " and his role is " + task->getResponsiblePicket()->getRole() << endl;

    return 0;
}
