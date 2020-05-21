//
// Created by Tiago on 12/05/2020.
//

#include <fstream>
#include <iostream>
//#include <Algorithms/TSP.h>

#include "Company.h"
#include "Utils/NecessaryFunctions_NameSpaces.h"

Company::Company(string name) {
    this->name = name;
    readPicketsFile("../files/pickets.txt");
    readTasksFile("../files/tasks.txt");
    readNodes("../maps/Porto/porto_strong_nodes_xy.txt");
    readEdges("../maps/Porto/porto_strong_edges.txt");
    setRandomNodesToTasks();
    beginTime = Time("01:00");
    endTime = Time("23:00");
    startVertexId = 27198;
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
//            this->cityGraph.addEdge(idNode1, idNode2, 1.0);
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

Graph<long> &Company::getCityGraph() {
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

void Company::setZonesToTasks() {
    for (auto task: tasks) {
        Vertex<long>* v = cityGraph.findVertex(task->getNodeId());
        task->setZone(v->getVZone());
    }
}

Time Company::getBeginTime() const {
    return beginTime;
}

Time Company::getEndTime() const {
    return endTime;
}

void Company::setBeginTime(const Time &time) {
    beginTime = time;
}

void Company::setEndTime(const Time &time) {
    endTime = time;
}

long Company::getStartVertexId() const {
    return startVertexId;
}

void Company::setStartVertexId(long vertexId) {
    startVertexId = vertexId;
}

void Company::setRandomNodesToTasks() {

    vector<Vertex<long>*> vertices = cityGraph.getVertexSet();
    int randomIndexNum;
    Vertex<long>* v;

    for (auto task: tasks) {
        randomIndexNum = rand() % vertices.size();
        v = vertices.at(randomIndexNum);
        vertices.erase(remove(vertices.begin(), vertices.end(), v), vertices.end()); // não podem haver tasks com o mesmo nodeId
        task->setNodeId(v->getInfo());
    }
}

Task *Company::getTaskById(long vertexId) {
    for (auto task: tasks) {
        if (task->getNodeId() == vertexId)
            return task;
    }
    return nullptr; // nunca chega aqui
}

void Company::setBestPathToPickets() {

    for (auto picket: pickets) {
        if (picket->getTasks().size() == 0)
            continue;

        TSP<long> tsp(&cityGraph, searchAlgorithm);
        vector<long> path = tsp.calculatePath(picket->getTasksIds(), startVertexId, startVertexId);
        picket->setPath(path);

        picket->setInitTime(beginTime);

        for (auto nodeId: path) {
            if (generalFunctions::inVector<long>(picket->getTasksIds(), nodeId)) {
                Task* task = getTaskById(nodeId);
                Time currentTime = picket->getCurrentTime();
                task->setBeginTime(currentTime);
                currentTime = currentTime.addMinutes(task->getDurationMinutes()+1);
                picket->setInitTime(currentTime);
            }
        }
    }

}

void Company::setSearchAlgorithm(SEARCH_ALGORITHM searchAlgorithm) {
    this->searchAlgorithm = searchAlgorithm;
}



