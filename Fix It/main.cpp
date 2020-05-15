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

    Company company("Fix It");

    mainMenu(company);

    /*
    GraphInterface graphI(1920, 1080);
    vector<Edge<long>*> edgesTotal;

    for(Vertex<long>* v: company.getCityGraph().getVertexSet()) {
        for(Edge<long>* e: v->getOutgoingEdges())
            edgesTotal.push_back(e);
    }
    graphI.displayOporto(edgesTotal);
    */
    

    return 0;
}
