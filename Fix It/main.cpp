#include <cstdio>
#include "src/GraphViewer/graphviewer.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "src/Picket.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Picket picket1("Ze Antone", "Qanalizadore");
    Picket picket2("Toine", "Iletrissista");
    Picket picket3("Bezaina", "Cassador de milfs");

    cout << "The name of the picket " + to_string(picket1.getId()) + " is " + picket1.getName() + " and his role is " + picket1.getRole() << endl;
    cout << "The name of the picket " + to_string(picket2.getId()) + " is " + picket2.getName() + " and his role is " + picket2.getRole() << endl;
    cout << "The name of the picket " + to_string(picket3.getId()) + " is " + picket3.getName() + " and his role is " + picket3.getRole() << endl;

    string newRole1 = "Mr steal your girl";
    picket1.setRole(newRole1);

    string newName2 = "Kulatra";
    picket2.setName(newName2);

    cout << endl;

    cout << "The name of the picket " + to_string(picket1.getId()) + " is " + picket1.getName() + " and his role is " + picket1.getRole() << endl;
    cout << "The name of the picket " + to_string(picket2.getId()) + " is " + picket2.getName() + " and his role is " + picket2.getRole() << endl;



    return 0;
}
