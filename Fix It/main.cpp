#include <cstdio>
#include "lib/graphviewer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Utils/Time.h>
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

    //mainMenu(company);

    /*
    GraphInterface graphI(1920, 1080);
    vector<Edge<long>*> edgesTotal;

    for(Vertex<long>* v: company.getCityGraph().getVertexSet()) {
        for(Edge<long>* e: v->getOutgoingEdges())
            edgesTotal.push_back(e);
    }
    graphI.displayOporto(edgesTotal);
    */

//    TSP<long> tsp(company.getCityGraph());
//
//    tsp.calculatePath({435240968, 435477344, 444004655}, 444004649, 444004644);

    Graph<long int> *g = company.getCityGraph();

    Dijkstra<long int> dijkstra(g);

    dijkstra.dijkstraShortestPath(1223751626, 1223751630);
    vector<long int> vec = g->getPath(1223751626, 1223751630);

    for (auto x: vec) {
        cout << x << endl;
    }
    


    return 0;
}
