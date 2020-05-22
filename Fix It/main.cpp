#include <iostream>

#include "Company.h"
#include "src/UserInterface/Menu.h"

using namespace std;

CITY readCityOption() {
    cout << "\n\nCities available: " << endl << endl;
    cout << "1. Porto" << endl;
    cout << "2. Penafiel" << endl;
    cout << "3. Espinho" << endl;
    cout << "4. Coimbra" << endl;
    cout << "5. Aveiro" << endl;
    cout << "6. Braga" << endl;
    cout << "7. Fafe" << endl;
    cout << "8. Gondomar" << endl;
    cout << "9. Lisboa" << endl;
    cout << "10. Maia" << endl;
    cout << "11. Viseu" << endl;
    cout << endl;

    int cityNum;
    do {
        cityNum = readOperations::readNumber<int>("Please chose the city of the company: ");
    } while (cityNum < 1 || cityNum > 12);

    cout << "\n\nLoading Maps..." << endl;

    return static_cast<CITY>(cityNum);
}

int main() {

    Company company("Fix It", readCityOption());

    mainMenu(company);

    return 0;
}
