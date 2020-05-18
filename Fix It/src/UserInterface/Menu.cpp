
#include "Menu.h"

#include <iostream>
#include <limits> // Used in numeric_limits<streamsize>::max()
#include <GraphInterface.h>
#include "../Algorithms/Clustering.h"

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
    vector<string> mainChoices = { "1. Display and Manage Pickets and Tasks", "2. View city graph", "3. Assign Tasks to the Pickets", "0. Exit" };
    vector<string> firstChoices = { "1. Display Pickets", "2. Display Tasks", "3. Create Picket", "4. Create Task", "0. Main Menu" };
    vector<string> secondChoices = { "1. Display Graph", "2. Display Clusters", "0. Main Menu" };
    vector<string> thirdChoices = { "1. Assign Tasks to the Pickets", "0. Main Menu" };
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
                option = displays(firstChoices, mainChoices.at(mainMenu - 1), companyName);
                switch (option)
                {
                    case 1:
                    {
                        company.showPicketsInfo();
                        cout << endl << endl << "Press any Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 2:
                    {
                        company.showTasksInfo();
                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    case 3:
                    {
                        company.createPicket();
                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    case 4:
                    {
                        company.createTask();
                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    default:
                        break;
                }
                break;
            case 2:
                option = displays(secondChoices, mainChoices.at(mainMenu - 1), companyName);
                switch (option)
                {
                    case 1:
                    {
                        /* Display Nodes */
                        GraphInterface graphI(1920, 1080);
                        vector<Edge<long>*> edgesTotal;

                        for(Vertex<long>* v: company.getCityGraph().getVertexSet()) {
                            for(Edge<long>* e: v->getOutgoingEdges())
                                edgesTotal.push_back(e);
                        }
                        graphI.displayOporto(edgesTotal, company.getCityGraph().getVertexSet());
//                        GraphInterface graphI(1920, 1080);
//                        graphI.displayOporto(company.getCityGraph().getVertexSet());
                        cout << endl << endl << "Press any Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 2:
                    {
                        vector<long> task_NodesIDs;
                        for(Task* task: company.getTasks())
                            task_NodesIDs.push_back(task->getNodeId());

                        Clustering<long> clusterAlg(&company.getCityGraph());
                        clusterAlg.calculateClustering(task_NodesIDs);

                        GraphInterface graphI(1920, 1080);
                        vector<Edge<long>*> edgesTotal;

                        for(Vertex<long>* v: company.getCityGraph().getVertexSet()) {
                            for(Edge<long>* e: v->getOutgoingEdges()) {
                                edgesTotal.push_back(e);
//                                if(e->getOrig()->getVZone() >= 1 && e->getOrig()->getVZone() <= 6)
//                                    cout << e->getOrig()->getInfo()<< endl;
                            }

                        }
                        graphI.displayOporto(edgesTotal, company.getCityGraph().getVertexSet());

                        cout << endl << endl << "Press any Enter to continue...";
                        cin.get();
                        break;
                    }
                    default:
                        break;
                }
                break;
            case 3:
                option = displays(thirdChoices, mainChoices.at(mainMenu - 1), companyName);
                switch (option)
                {
                    case 1:
                    {


                        cout << endl << endl << "Press any Enter to continue...";
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
