#include <iostream>

#include "Company.h"
#include "src/UserInterface/Menu.h"

using namespace std;

int main() {
    cout << "Loading Maps..." << endl;
    Company company("Fix It");

    mainMenu(company);

    return 0;
}
