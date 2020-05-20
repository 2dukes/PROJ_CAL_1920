#include <cstdio>
#include "lib/graphviewer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Utils/Time.h>
#include <Algorithms/Dijkstra.h>
#include <Algorithms/TSP.h>

using namespace std;

#include "src/Picket.h"
#include "src/Task.h"
#include "Company.h"
#include "src/Utils/NecessaryFunctions_NameSpaces.h"
#include "src/UserInterface/Menu.h"
#include "GraphInterface.h"

int main() {

    Company company("Fix It");

    mainMenu(company);

    Dijkstra<long> dijkstra((Graph<long> *) &company.getCityGraph());
    dijkstra.dijkstraShortestPath(1, 10);
    vector<long int> BAIDARdeu = company.getCityGraph().getPath(1, 10);

//    for(auto vertex: BAIDARdeu) {
//        cout << vertex << endl;
//    }

//    GraphInterface graphI(1920, 1080);
//    graphI.displayPath(company.getCityGraph().getVertexSet());

    TSP<long> newTSP(&company.getCityGraph());
    vector<long> pois {10, 20, 30, 40, 50, 60, 70};
    vector<long> BAIDAR = newTSP.calculatePath(pois, 1, 1);

    for(auto vertex: BAIDAR) {
        cout << vertex << endl;
    }

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
