//
// Created by Tiago on 12/05/2020.
//

#include <fstream>
#include <iostream>

#include "Company.h"
#include "Utils/NecessaryFunctions_NameSpaces.h"

Company::Company(string name) {
    this->name = name;
    readPicketsFile("../files/pickets.txt");
    readTasksFile("../files/tasks.txt");
    cout << "Working" << endl;
    readCityGraph("../maps/Porto/nodes_x_y_porto.txt", "../maps/Porto/edges_porto.txt");
    cout << "Working..." << endl;
}

string Company::getName() {
    return name;
}

bool Company::readPicketsFile(const string& filename) {
    ifstream f;
    f.open(filename);
    int tasksDone;
    string name, aux;
    char delim = ' ';
    vector<string> roles;
    if (f.is_open()) {
        while(!f.eof()) {
            getline(f, aux, delim);
            getline(f, name);
            getline(f, aux, delim);
            getline(f, aux);
            roles = generalFunctions::separate_string(aux, ',');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> tasksDone;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux);

            Picket* picket = new Picket(name, roles, tasksDone);
            addPicket(picket);
            roles.clear();

        }
        f.close();
        return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }
}

bool Company::readTasksFile(const string& filename) {
    ifstream f;
    f.open(filename);
    int duration;
    long int nodeId;
    string function, aux;
    char delim = ' ';
    if (f.is_open()) {
        while(!f.eof()) {
            getline(f, aux, delim);
            getline(f, function);
            getline(f, aux, delim);
            f >> nodeId;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> duration;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux);

            Task* task = new Task(function, nodeId, duration);
            addTask(task);
        }
        f.close();
        return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }
}

bool Company::writePicketsFile(const string& filename) {
    ofstream f;
    f.open(filename, ios::out);
    if (f.is_open()) {
        for (auto it = pickets.begin(); it != pickets.end(); it++) {
            f << **it;
            if (it != pickets.end() - 1)
                f << endl << "::::::::::" << endl << endl;
        }
        f.close();
        return true;
    }
    else {
        cerr << "Error opening the file " << filename << endl;
        return false;
    }
}

bool Company::writeTasksFile(const string& filename) {
    ofstream f;
    f.open(filename, ios::out);
    if (f.is_open()) {
        for (auto it = tasks.begin(); it != tasks.end(); it++) {
            f << **it;
            if (it != tasks.end() - 1)
                f << endl << "::::::::::" << endl << endl;
        }
        f.close();
        return true;
    }
    else {
        cerr << "Error opening the file " << filename << endl;
        return false;
    }
}

void Company::addPicket(Picket* picket) {
    this->pickets.push_back(picket);
}

void Company::addTask(Task* task) {
    this->tasks.push_back(task);
}

vector<Picket *> Company::getPickets() {
    return pickets;
}

vector<Task *> Company::getTasks() {
    return tasks;
}

Company::~Company() {
    writePicketsFile("../files/pickets.txt");
    writeTasksFile("../files/tasks.txt");

    auxiliaryDestructor(pickets);
    auxiliaryDestructor(tasks);
}

bool Company::readNodes(const string &filename) {
    cout << "Nodes" << endl;
    ifstream f;
    f.open(filename);
    long int id, aux;
    double x, y;
    string line;
    //double minX = INF, minY = INF, maxX = INF_NEG, maxY = INF_NEG;

    if (f.is_open()) {
        f >> aux; // ignorar primeira linha
        f.clear();
        f.ignore(1000, '\n');
        while(!f.eof()) {
            getline(f, line);
            if (sscanf(line.c_str(), "(%ld, %lf, %lf)", &id, &x, &y) != 3) {
                cerr << "Error reading the file " << filename << endl;
                return false;
            }
            cout << "After" << endl;
            Vertex<long int> vertex(id);
            cout << "ID: " << id << endl;
            cout << "X: " << x << endl;
            cout << "Y: " << y << endl;
            this->cityGraph->addVertex(id, x, y); // Tá a dar erro aqui
            cout << "Graph4" << endl;
            //generalFunctions::processCoordinates(x, y, minX, minY, maxX, maxY);
//            printf("X: %lf | T: %lf\n", this->cityGraph.findVertex(id)->getX(),x);
        }
        f.close();
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }
    /*
    printf("MaxX: %lf | MaxY: %lf | MinX: %lf | MinY: %lf\n", maxX, maxY, minX, minY);
    double halfX = (maxX + minX) / 2;
    double halfY = (maxY + minY) / 2;
    printf("HALFX: %lf | HALFY: %lf \n", halfX, halfY);

    for(auto vertex: this->cityGraph->getVertexSet()) {
        if(vertex->getX() >= halfX) {
            if(vertex->getY() >= halfY) // ZONE TOP_RIGHT
                vertex->setVZone(ZONE1);
            else                       // ZONE BOTTOM_RIGHT
                vertex->setVZone(ZONE3);
        }
        else {
            if(vertex->getY() >= halfY)  // ZONE TOP_LEFT
                vertex->setVZone(ZONE2);
            else                        // ZONE BOTTOM_LEFT
                vertex->setVZone(ZONE4);
        }
    }
    */
    return true;
}

bool Company::readEdges(const string &filename) {
    cout << "Edges" << endl;
    ifstream f;
    f.open(filename);
    long int idNode1, idNode2, aux;
    string line;
    if (f.is_open()) {
        f >> aux; // ignorar primeira linha
        f.clear();
        f.ignore(1000, '\n');
        while(!f.eof()) {
            getline(f, line);
            if (sscanf(line.c_str(), "(%ld, %ld)", &idNode1, &idNode2) != 2) {
                cerr << "Error reading the file " << filename << endl;
                return false;
            }
            this->cityGraph->addEdge(idNode1, idNode2,
                    generalFunctions::heuristicDistance<long int>(this->cityGraph->findVertex(idNode1),
                                                             this->cityGraph->findVertex(idNode2)));
        }
        f.close();
        return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }
}

bool Company::readCityGraph(const string &nodesFile, const string &edgesFile) {
    return readNodes(nodesFile) && readEdges(edgesFile);
}

Graph<long> *Company::getCityGraph() const {
    return cityGraph;
}

void Company::showPicketsInfo() const {
    for (Picket *picket: pickets) {
        cout << *picket << endl;
    }
}

void Company::showTasksInfo() const {
    for (Task *task: tasks) {
        cout << *task << endl;
    }
}

bool Company::createPicket() {
    string name = readOperations::readString("Name:");
    cout << "Enter the roles of the picket; write 'exit' to stop" << endl;
    vector<string> roles = readOperations::readVectorString("Role: ");
    int tasksDone = readOperations::readNumber<int>("Tasks Done: ");

    cout << endl << "Are you sure you want to insert the following data? (Y|N)" << endl << endl;
    Picket* picket = new Picket(name, roles, tasksDone);
    cout << *picket << endl;

    string answer = readOperations::confirmAnswer();
    if(answer == "Y" || answer == "y") {
        addPicket(picket);
        cout << "Data successfully inserted!" << endl;
        return true;
    }
    cout << "Data not inserted." << endl;
    delete picket;
    return false;
}

bool Company::createTask() {
    string function = readOperations::readRole("Function:");

    int nodeId = readOperations::readNumber<long int>("Node ID: ");

    int duration = readOperations::readNumber<int>("Duration: ");

    cout << endl << "Are you sure you want to insert the following data? (Y|N)" << endl << endl;
    Task* task = new Task(function, nodeId, duration);
    cout << *task << endl;

    string answer = readOperations::confirmAnswer();
    if(answer == "Y" || answer == "y") {
        addTask(task);
        cout << "Data successfully inserted!" << endl;
        return true;
    }
    cout << "Data not inserted." << endl;
    delete task;
    return false;
}


