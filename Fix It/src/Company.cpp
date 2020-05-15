//
// Created by Tiago on 12/05/2020.
//

#include <fstream>
#include <iostream>
#include <iomanip>

#include "Company.h"
#include "Utils/NecessaryFunctions_NameSpaces.h"

Company::Company(string name) {
    this->name = name;
    readPicketsFile("../files/pickets.txt");
    readTasksFile("../files/tasks.txt");
    readNodes("../maps/Porto/nodes_x_y_porto.txt");
    readEdges("../maps/Porto/edges_porto.txt");
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
            f << "Name: " << (*it)->getName() << endl;
            f << "Roles: ";
            f << generalFunctions::coutVectorString((*it)->getRoles());
            f << endl << "Tasks Done: " << (*it)->getNumTasksDone();

            if (it != pickets.end() - 1)
                f << endl << endl << "::::::::::" << endl << endl;
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
    return false;
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
    ifstream f;
    f.open(filename);
    long int id, aux;
    double x, y;
    string line;

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
            Vertex<long int> vertex(id);
            this->cityGraph.addVertex(id, x, y);
        }
        f.close();
        return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }
}

bool Company::readEdges(const string &filename) {
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
            this->cityGraph.addEdge(idNode1, idNode2,
                    generalFunctions::heuristicDistance<long int>(this->cityGraph.findVertex(idNode1),
                                                             this->cityGraph.findVertex(idNode2)));
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

const Graph<long> &Company::getCityGraph() const {
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


