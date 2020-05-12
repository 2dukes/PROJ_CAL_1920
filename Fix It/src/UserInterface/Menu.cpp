
#include "Menu.h"

#include <iostream>
#include <limits> // Used in numeric_limits<streamsize>::max()

using namespace std;

int displays(vector<string> &displays, string explorer, string &companyName) {
    int option;

    cout << string(100, '\n');
    explorer = companyName + " | " + explorer;
    cout << explorer << endl << endl << endl;
    for (size_t i = 0; i < displays.size(); i++)
        cout << "\t" << displays.at(i) << endl;
    cout << endl << endl;
    cout << "Option: "; cin >> option;
    while (cin.fail() || !(option >= 0 && option <= (displays.size() - 1))) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid Option! Please enter a valid number." << endl << endl;
        cout << "Option: "; cin >> option;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return option;
}

void mainMenu(Company &company) {

    int option, mainMenu, option1, option2;
    string companyName = company.getName();

    cout << string(100, '\n');
    vector<string> mainChoices = { "1. Display", "2. Manage", "0. Exit" };
    vector<string> manageChoices = { "1. Create", "2. Alter", "3. Remove", "0. Main Menu" };
    vector<string> manageSecundaryChoices = { "1. Other Worker", "0. Previous Menu" };
    vector<string> viewAvailablePackChoices = { "1. Other Workers", "0. Main Menu" };

    do
    {

        cout << string(100, '\n'); cout << "====== " << companyName << " ======" << endl << endl << endl;

        for (size_t i = 0; i < mainChoices.size(); i++)
            cout << "\t" << mainChoices.at(i) << endl;

        cout << endl << endl << "Option: ";
        cin >> mainMenu;

        while (cin.fail() || !(mainMenu >= 0 && mainMenu <= (mainChoices.size() - 1)))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid Option! Please enter a valid number." << endl << endl;
            cout << "Option: "; cin >> mainMenu;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean NL line feed

        switch (mainMenu)
        {
            case 1:
                // Option 1.
                option = displays(viewAvailablePackChoices, mainChoices.at(mainMenu - 1), companyName);
                switch (option)
                {
                    case 1:
                    {
                        // Display | Other Workers
                        //company.displayOtherWorkers();
                        cout << endl << endl << "Press any Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 2:
                    {
                        /// Display | Technical Team

                        //company.displayTechnicalTeamMembers();
                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    default:
                        break;
                }
                break;
            case 2:
                option = displays(viewAvailablePackChoices, mainChoices.at(mainMenu - 1), companyName);
                switch (option)
                {
                    case 1:
                    {
                        // Display | Other Workers
                        //company.displayOtherWorkers();
                        cout << endl << endl << "Press any Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 2:
                    {
                        /// Display | Technical Team

                        //company.displayTechnicalTeamMembers();
                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    } while (mainMenu != 0);
}
