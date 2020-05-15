#include <cstdio>
#include "lib/graphviewer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Utils/Time.h>

using namespace std;

#include "src/Picket.h"
#include "src/Task.h"
#include "Company.h"
#include "src/Utils/NecessaryFunctions_NameSpaces.h"
#include "src/UserInterface/Menu.h"
#include "GraphInterface.h"

int main() {
    /*
    Time beginTime1("12:30");
    Time endTime1("15:10");

    Time beginTime2("15:11");
    Time endTime2("16:20");

    vector<string> roles;
    roles.push_back("Eletricista");
    roles.push_back("Canalisador");

    Picket* picket = new Picket("Ze", roles, 0);

    Task* task1 = new Task("Eletricista", "12.214, 13.214", beginTime1, endTime1);
    Task* task2 = new Task("Canalisador", "13.214, 14.214", beginTime2, endTime2);

    picket->addTask(task1);
    picket->addTask(task2);

    cout << "Num tasks done: " << to_string(picket->getNumTasksDone()) << endl;
    */

    Company company("Fix It"); // TODO UNCOMMENT Company CONSTRUCTOR & DESTRUCTOR!

    //mainMenu(company);
    company.readNodes("../maps/Porto/nodes_x_y_porto.txt");
    company.readEdges("../maps/Porto/edges_porto.txt");

    /* Display Nodes */
//    GraphInterface graphI(1920, 1080);
//    graphI.displayPath(company.getCityGraph().getVertexSet());

    GraphInterface graphI(1920, 1080);
    vector<Edge<long>*> edgesTotal;

    for(Vertex<long>* v: company.getCityGraph().getVertexSet()) {
        for(Edge<long>* e: v->getOutgoingEdges())
            edgesTotal.push_back(e);
    }
    graphI.displayOporto(edgesTotal);


    cout << "Hello World!" << endl;
    return 0;
}
