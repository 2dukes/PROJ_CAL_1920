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

    Company company("Fix It");

    //mainMenu(company);

    // ===========================================Tasks Divided By Zone==============================

    vector<long> task_NodesIDs;
    for(Task* task: company.getTasks())
        task_NodesIDs.push_back(task->getNodeId());

    Clustering<long> clusterAlg(&company.getCityGraph());
    clusterAlg.calculateClustering(task_NodesIDs);

    company.setZonesToTasks();

    company.setStartVertexId(159);

    Pairing pairing(company.getTasks(), company.getPickets(), company.getBeginTime(), company.getEndTime(), &company.getCityGraph(), company.getStartVertexId());

//    vector<vector<Task*>> tz = pairing.getTasksByZone();

//    for (int i = 0; i < tz.size(); i++) {
//        for (int j = 0; j < tz.at(i).size(); j++) {
//            cout << "Task with id: " << tz.at(i).at(j)->getNodeId() << endl;
//            cout << "Zone " <<  tz.at(i).at(j)->getZone() << endl;
//            cout << "-------------------------" << endl;
//        }
//    }

    pairing.setTasksToPickets();

    // ==============================================================================================








//    GraphInterface graphI(1920, 1080);
//    graphI.displayPath(company.getCityGraph().getVertexSet());

//    TSP<long> newTSP(&company.getCityGraph());
//    vector<long> pois {10, 20, 30, 40, 50, 60, 70};
//    vector<long> BAIDAR = newTSP.calculatePath(pois, 1, 100);
//
//    for(auto vertex: BAIDAR) {
//        cout << vertex << endl;
//    }

//    Graph<long>* g = const_cast<Graph<long> *>(&(company.getCityGraph()));
//
//    Dijkstra<long int> dijkstra(g);
//
//    dijkstra.dijkstraShortestPath(100, 210);
//    vector<long int> vec = g->getPath(100, 210);
//
//    for(auto vertex: vec) {
//        cout << vertex << endl;
//    }

    return 0;
}
