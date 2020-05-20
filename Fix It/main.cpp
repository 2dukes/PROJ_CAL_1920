#include <cstdio>
#include "lib/graphviewer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Utils/Time.h>
#include <Algorithms/Dijkstra.h>
#include <Algorithms/TSP.h>
#include <Algorithms/Pairing.h>
#include <Algorithms/Clustering.h>

using namespace std;

#include "src/Picket.h"
#include "src/Task.h"
#include "Company.h"
#include "src/Utils/NecessaryFunctions_NameSpaces.h"
#include "src/UserInterface/Menu.h"
#include "GraphInterface.h"

int main() {
    cout << "Loading Maps..." << endl;
    Company company("Fix It");

    //mainMenu(company);

  
    /*
    vector<long> task_NodesIDs;
    for(Task* task: company.getTasks())
        task_NodesIDs.push_back(task->getNodeId());

    
    Clustering<long> clusterAlg(&company.getCityGraph());
    clusterAlg.calculateClustering(task_NodesIDs);

    TSP<long> newTSP(&company.getCityGraph());
    vector<long> pois {26323, 53170};
    vector<long> BAIDAR = newTSP.calculatePath(pois, 53492, 26590);
    */

    company.setZonesToTasks();

    company.setStartVertexId(159);
    company.setBeginTime(Time("9:00"));
    company.setEndTime(Time("17:30"));

    Pairing pairing(company.getTasks(), company.getPickets(), company.getBeginTime(), company.getEndTime(), &company.getCityGraph(), company.getStartVertexId());

//    vector<vector<Task*>> tz = pairing.getTasksByZone();

//    for (int i = 0; i < tz.size(); i++) {
//        for (int j = 0; j < tz.at(i).size(); j++) {
//            cout << "Task with id: " << tz.at(i).at(j)->getNodeId() << endl;
//            cout << "Zone " <<  tz.at(i).at(j)->getZone() << endl;
//            cout << "-------------------------" << endl;
//        }
//    }

    // ==============================================================================================

    // ===========================================SET TASKS TO PICKETS==============================
    // ainda tenho que meter isto na classe Company; não retirar da main para já :)

    pairing.setTasksToPickets();

    vector<Task*> tasksPaired = company.getTasks();

    for (auto task: tasksPaired) {
        if (task->hasPicket()) {
            cout << "Task with ID = " << task->getNodeId() << " and zone = " << task->getZone() << endl;
            cout << "Function: " << task->getFunction() << endl;
            cout << "Begin Time: " << task->getBeginTime() << endl;
            cout << "End Time: " << task->getEndTime() << endl;
            cout << "Picket chosen: " << task->getResponsiblePicket()->getName() << " (ID= " << task->getResponsiblePicket()->getId() << ")" << endl;
            cout << "-------------------------------------------\n";
        }
        else {
            cerr << "The task with id " << task->getNodeId() << " does not have a compatible picket" << endl;
            cout << "-------------------------------------------\n";
        }
    }

    // ==============================================================================================


    return 0;
}
