#include <iostream>

#include "Company.h"
#include "src/UserInterface/Menu.h"
#include "Algorithms/SCC.h"

using namespace std;

int main() {
    cout << "Loading Maps..." << endl;
    Company company("Fix It");
    SCC strongComponents(&company.getCityGraph());
    vector<vector<long>> SCCVector = strongComponents.calculateSCCs();

    cout << SCCVector.size() << endl << SCCVector.at(0).size() << endl; // Number of Trees | Respective Content

    mainMenu(company);

    return 0;
}
