
#include "Menu.h"

#include <iostream>
#include <limits> // Used in numeric_limits<streamsize>::max()
#include <GraphInterface.h>
#include <Algorithms/Pairing.h>
#include "../Algorithms/Clustering.h"
#include "../Algorithms/Square.h"

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
    vector<string> mainChoices = { "1. Manage company", "2. View city graph", "3. Assign Tasks to the Pickets", "0. Exit" };
    vector<string> firstChoices = { "1. Display Pickets", "2. Display Tasks", "3. Create Picket", "4. Create Task", "5. Change the company's working hours", "6. Change the company's headquarters", "7. Limit number of pickets", "8. Limit number of tasks", "0. Main Menu" };
    vector<string> secondChoices = { "1. Display Graph", "2. Display & Generate Clusters' Tasks", "0. Main Menu" };
    vector<string> thirdChoices = { "1. Assign Tasks to the Pickets", "0. Main Menu" };
    vector<string> viewAvailablePackChoices = { "1. Other Workers", "0. Main Menu" };

    do
    {

        cout << string(100, '\n'); cout << "====== " << companyName << " ======" << endl << endl;
        cout << "   At your disposal from " << company.getBeginTime() << " to " << company.getEndTime() << " from the vertex ID " << company.getStartVertexId() << " to the world " << endl << endl << endl;

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
                        cout << "\n\n";
                        company.showPicketsInfo();
                        cout << endl << endl << "Press any Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 2:
                    {
                        cout << "\n\n";
                        company.showTasksInfo();
                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    case 3:
                    {
                        cout << "\n\n";
                        company.createPicket();
                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    case 4:
                    {
                        cout << "\n\n";
                        company.createTask();
                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    case 5:
                    {
                        Time beginTime, endTime;
                        do {
                            cout << "\n\n";

                            do {
                                string timeStr = readOperations::readString("Enter the start time of the working day: (hh:mm) ");
                                beginTime = Time(timeStr);
                            } while (beginTime == Time(0, 0));

                            cout << "\n\n";

                            do {
                                string timeStr = readOperations::readString("Enter the end time of the working day: (hh:mm) ");
                                endTime = Time(timeStr);
                            } while (endTime == Time(0, 0));
                        } while (endTime < beginTime || endTime == beginTime);

                        company.setBeginTime(beginTime);
                        company.setEndTime(endTime);

                        cout << "The start time of the working day is now " << beginTime << " and the end time is " << endTime;

                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    case 6:
                    {
                        int nodeId;
                        Vertex<long> * v;
                        do {
                            cout << "\n\n";
                            nodeId = readOperations::readNumber<long>("Enter the vertex ID of the company's headquarters: ");
                            v = company.getCityGraph().findVertex(nodeId);
                            if (v == nullptr)
                                cout << "\n\nThere is no such vertex in the city's graph, please enter a valid vertex ID\n\n";
                        } while(v == nullptr);

                        company.setStartVertexId(nodeId);

                        cout << endl << endl << "The company's headquarters is now in the vertex with ID " << nodeId << endl << endl;

                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    case 7:
                    {
                        int numPickets;
                        do {
                            numPickets = readOperations::readNumber<int>("Please enter the maximum number of pickets: ");
                        } while (numPickets <= 0);

                        company.limitNumPickets(numPickets);

                        cout << endl << endl << "Press any key to continue...";
                        cin.get();
                        break;
                    }
                    case 8:
                    {
                        int numTasks;
                        do {
                            numTasks = readOperations::readNumber<int>("Please enter the maximum number of tasks: ");
                        } while (numTasks <= 0);

                        company.limitNumTasks(numTasks);


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
                        GraphInterface graphI(1920, 1080, &company.getCityGraph(), &company);
                        vector<Edge<long>*> edgesTotal;

                        for(Vertex<long>* v: company.getCityGraph().getVertexSet()) {
                            v->setVZone(ZONE0);
                            for(Edge<long>* e: v->getOutgoingEdges())
                                edgesTotal.push_back(e);
                        }

                        graphI.displayOporto(edgesTotal, company.getCityGraph().getVertexSet(), company.getStartVertexId());
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

                        Square<long> squareAlg(&company.getCityGraph());
                        squareAlg.calculateSquare(task_NodesIDs);

                        GraphInterface graphI(1920, 1080, &company.getCityGraph(), &company);
                        vector<Edge<long>*> edgesTotal;

                        for(Vertex<long>* v: company.getCityGraph().getVertexSet()) {
                            for(Edge<long>* e: v->getOutgoingEdges()) {
                                edgesTotal.push_back(e);
//                                if(e->getOrig()->getVZone() >= 1 && e->getOrig()->getVZone() <= 6)
//                                    cout << e->getOrig()->getInfo()<< endl;
                            }

                        }
                        graphI.displayOporto(edgesTotal, company.getCityGraph().getVertexSet(), company.getStartVertexId());

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
                        int algOption;
                        do {
                            algOption = readOperations::readNumber<int>("Please choose a search algorithm to use in TSP algorithm:\n\n0. Dijkstra\n1. AStar\n\nOption (0 / 1): ");
                        } while (algOption != 0 && algOption != 1);

                        for (auto picket: company.getPickets()) {
                            picket->clearTasks();
                        }
                        for (auto task: company.getTasks()) {
                            Time t = company.getBeginTime();
                            task->setBeginTime(t);
                            task->removeResponsiblePicket();
                        }

                        company.setSearchAlgorithm(static_cast<SEARCH_ALGORITHM>(algOption));

                        cout << endl << endl << "Number of tasks: " << company.getTasks().size() << endl;
                        cout << "Number of pickets: " << company.getPickets().size() << endl << endl;

                        cout << endl << endl << "Executing a complex algorithm..." << endl << endl;
                        vector<long> task_NodesIDs;
                        for(Task* task: company.getTasks())
                            task_NodesIDs.push_back(task->getNodeId());

                        Square<long> clusterAlg(&company.getCityGraph());
                        clusterAlg.calculateSquare(task_NodesIDs);

                        company.setZonesToTasks();

                        Pairing pairing(company.getTasks(), company.getPickets(), company.getBeginTime(), company.getEndTime());
                        pairing.setTasksToPickets();
                        company.setBestPathToPickets();

                        vector<Task*> tasksPaired = company.getTasks();

                        cout << "\n\n=================================TASKS WITH PICKETS==================================================\n\n";

                        int numTasksWithPicket = 0, numTasksWithoutPicket = 0;
                        for (auto task: tasksPaired) {
                            if (task->hasPicket()) {
                                cout << "Task with ID = " << task->getNodeId() << " and zone = " << task->getZone() << endl;
                                cout << "Function: " << task->getFunction() << endl;
                                cout << "Begin Time: " << task->getBeginTime() << endl;
                                cout << "End Time: " << task->getEndTime() << endl;
                                cout << "Picket chosen: " << task->getResponsiblePicket()->getName() << " (ID= " << task->getResponsiblePicket()->getId() << ")" << endl;
                                cout << "-------------------------------------------\n";
                                numTasksWithPicket++;
                            }
                        }

                        cout << "\n\n\n\n========================TASKS WITHOUT PICKETS=================================================\n\n";

                        for (auto task: tasksPaired) {
                            if (!task->hasPicket()) {
                                cout << "Task with ID = " << task->getNodeId() << " and zone = " << task->getZone() << endl;
                                cout << "Function: " << task->getFunction() << endl;
                                cout << "Duration: " << task->getDurationMinutes() << endl;
                                cout << "-------------------------------------------\n";
                                numTasksWithoutPicket++;
                            }
                        }

                        // ==============================================================================================

                        cout << "\n\n\n\n============================PICKETS WITH TASKS=================================================\n\n";

                        int numPicketsWithTasks = 0, numPicketsWithoutTasks = 0;
                        vector<Picket*> picketsWithTasks = company.getPickets();
                        for (auto picket: picketsWithTasks) {
                            if (picket->getTasks().size() > 0) { // se pelo menos uma tarefa atribuida
                                cout << "Picket with id " << picket->getId() << " and zone " << picket->getZone() << endl;
                                cout << "His tasks are: \n";
                                vector<Task*> picketTasks = picket->getTasks();
                                for (auto task: picketTasks) {
                                    cout << endl << *task << endl;
                                }
                                cout << "--------------------------------------\n";
                                numPicketsWithTasks++;
                            }
                            else
                                numPicketsWithoutTasks++;
                        }

                        cout << "\n\n\nNumber of tasks attributed to a picket: " << numTasksWithPicket << endl;
                        cout << "Number of tasks not attributed to a picket: " << numTasksWithoutPicket << endl;
                        cout << "Number of pickets that needed to work: " << numPicketsWithTasks << endl;
                        cout << "Number of pickets that did not work: " << numPicketsWithoutTasks << endl << endl << endl;

                        GraphInterface graphI(1920, 1080, &company.getCityGraph(), &company);
                        vector<Edge<long>*> edgesTotal;

                        for(Vertex<long>* v: company.getCityGraph().getVertexSet()) {
                            for(Edge<long>* e: v->getOutgoingEdges())
                                edgesTotal.push_back(e);
                        }

                        vector<Picket*> pickets = company.getPickets();

                        int opt;
                        cout << "Display Tasks by: " << endl << endl;
                        cout << "0. Back" << endl;
                        cout << "1. Zone" << endl;
                        cout << "2. Picket ID" << endl;
                        cin >> opt;

                        switch(opt) {
                            case 1:
                            {
                                cout << "We're currently dividing our region in 4 different Zones." << endl;

                                vector<int> zoneX_numPickets;
                                vector<int> minTaskX_Pickets;

                                int auxVar;

                                for (int zone = 1; zone <= 4; zone++) {
                                    cout << endl << "For Zone " << zone << " how many Pickets do you want do display? ";
                                    cin >> auxVar;
                                    if(auxVar < 0) {
                                        cout << "Invalid Number!" << endl << endl;
                                        zone--;
                                        continue;
                                    }
                                    zoneX_numPickets.push_back(auxVar);
                                    cout << endl << "For Zone " << zone << " select the minimum of Tasks for each Picket: ";
                                    cin >> auxVar;
                                    if(auxVar < 0) {
                                        cout << "Invalid Number!" << endl << endl;
                                        zone--;
                                        continue;
                                    }
                                    minTaskX_Pickets.push_back(auxVar);
                                }

                                for (int zone = 1; zone <= 4; zone++) {
                                    cout << endl << "Displaying Tasks For Zone " << zone << ": " << endl;
                                    int numPicketsToDiplay = zoneX_numPickets.at(zone - 1);

                                    if(numPicketsToDiplay > 0) {
                                        for(auto picket: pickets) {
                                            if(picket->getTasks().size() >= minTaskX_Pickets.at(zone - 1) && picket->getZone() == zone) {
                                                cout << endl << "Displaying path of picket with ID = " << picket->getId() << "... " << endl;
                                                graphI.displayPath(edgesTotal, company.getCityGraph().getVertexSet(), picket->getPath(), picket->getTasksIds(), company.getStartVertexId());

                                                if(--numPicketsToDiplay <= 0)
                                                    break;
                                            }
                                        }
                                    }
                                    cout << endl << endl << "Finished Display For Zone" << zone << "!" << endl;
                                }
                                break;
                            }
                            case 2:
                            {
                                int picketID;
                                bool hasFound = false;

                                while(!hasFound) {
                                    cout << endl << endl << "Enter Picket ID: ";
                                    cin >> picketID;
                                    for(auto picket: company.getPickets()) {
                                        if(picket->getId() == picketID) {
                                            if(picket->getTasksIds().size() > 0)
                                                graphI.displayPath(edgesTotal, company.getCityGraph().getVertexSet(), picket->getPath(), picket->getTasksIds(), company.getStartVertexId());
                                            else
                                                cout << endl << "Picket has 0 Tasks assigned!" << endl;
                                            hasFound = true;
                                            break;
                                        }
                                    }
                                    if(!hasFound)
                                        cout << endl << "No Picket with That ID was Found. Please Enter another!" << endl << endl;
                                }
                                break;
                            }
                        }

                        cout << endl << endl << "Press any Enter to continue...";
                        cin.get();
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
