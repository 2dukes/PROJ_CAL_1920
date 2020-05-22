#include <fstream>
#include <iostream>

#include "Company.h"
#include "Algorithms/SCC.h"


Company::Company(string name, CITY cityNum) {
    this->name = name;
    readPicketsFile("../files/pickets.txt");
    readTasksFile("../files/tasks.txt");

    if (cityNum == Porto) {
        readCityGraph("../maps/Porto/porto_strong_nodes_xy.txt", "../maps/Porto/porto_strong_edges.txt");
    }
    else if (cityNum == Penafiel) {
        readCityGraph("../maps/Penafiel/penafiel_strong_nodes_xy.txt", "../maps/Penafiel/penafiel_strong_edges.txt");
    }
    else if (cityNum == Espinho) {
        readCityGraph("../maps/Espinho/espinho_strong_nodes_xy.txt", "../maps/Espinho/espinho_strong_edges.txt");
    }
    else if (cityNum == Coimbra) {
        readCityGraph("../maps/Coimbra/nodes_x_y_coimbra.txt", "../maps/Coimbra/edges_coimbra.txt");
    }
    else if (cityNum == Aveiro) {
        readCityGraph("../maps/Aveiro/nodes_x_y_aveiro.txt", "../maps/Aveiro/edges_aveiro.txt");
    }
    else if (cityNum == Braga) {
        readCityGraph("../maps/Braga/nodes_x_y_braga.txt", "../maps/Braga/edges_braga.txt");
    }
    else if (cityNum == Fafe) {
        readCityGraph("../maps/Fafe/nodes_x_y_fafe.txt", "../maps/Fafe/edges_fafe.txt");
    }
    else if (cityNum == Gondomar) {
        readCityGraph("../maps/Gondomar/nodes_x_y_gondomar.txt", "../maps/Gondomar/edges_gondomar.txt");
    }
    else if (cityNum == Lisboa) {
        readCityGraph("../maps/Lisboa/nodes_x_y_lisboa.txt", "../maps/Lisboa/edges_lisboa.txt");
    }
    else if (cityNum == Maia) {
        readCityGraph("../maps/Maia/nodes_x_y_maia.txt", "../maps/Maia/edges_maia.txt");
    }
    else if (cityNum == Viseu) {
        readCityGraph("../maps/Viseu/nodes_x_y_viseu.txt", "../maps/Viseu/edges_viseu.txt");
    }
    else {
        cerr << "There is no map!\n";
        exit(1);
    }
    setRandomNodesToTasks();
    sortPicketsByNumTasksDone();

    beginTime = Time("08:30");
    endTime = Time("17:30");
    startVertexId = cityGraph.getVertexSet().at(0)->getInfo();
    Vertex<long> *v = cityGraph.findVertex(startVertexId);
    if (v == nullptr) {
        cerr << "\n\nThere is no such vertex in the city's graph\n\n";
        exit(2);
    }
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

vector<Picket *> Company::getPickets() const {
    vector<Picket*> picketsLimited;
    int i = 0;
    int aux = maxNumPickets;
    while (aux-- > 0 && i < pickets.size()) {
        picketsLimited.push_back(pickets.at(i++));
    }
    return picketsLimited;
}

vector<Task *> Company::getTasks() const {
    vector<Task*> tasksLimited;
    int i = 0;
    int aux = maxNumTasks;
    while (aux-- > 0 && i < tasks.size()) {
        tasksLimited.push_back(tasks.at(i++));
    }
    return tasksLimited;
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
            int flag;
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

void Company::readCityGraph(const string &nodesFile, const string &edgesFile) {
    readNodes(nodesFile);
    readEdges(edgesFile);

    SCC strongComponents(&cityGraph);
    vector<vector<long>> SCCVector = strongComponents.calculateSCCs();
    long maxTreeSize = -INF;
    vector<long> selectedTree;
//    cout << SCCVector.size() << " | " << SCCVector.at(0).size() << endl; // Number of Trees | Respective Content Length
    if(SCCVector.at(0).size() == cityGraph.getVertexSet().size())
        cout << "Graph is a Strongly Connected Component!" << endl;
    for(auto SCCTree: SCCVector) {
        int aux = SCCTree.size();
        if(aux > maxTreeSize) {
            maxTreeSize = aux;
            selectedTree = SCCTree;
        }
    }

    cout << SCCVector.size() << " | " << maxTreeSize << endl; // Number of Trees | Respective Content Length

    cityGraph.deleteUnusefulNodes(selectedTree);
    cityGraph.deleteUnusefulEdges(selectedTree);


}

Graph<long> &Company::getCityGraph() {
    return cityGraph;
}

void Company::showPicketsInfo() const {
    for (Picket *picket: getPickets()) {
        cout << *picket << endl;
    }
}

void Company::showTasksInfo() const {
    for (Task *task: getTasks()) {
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

    long nodeId;
    Vertex<long> *v;
    do {
        nodeId = readOperations::readNumber<long int>("Node ID: ");

        v = cityGraph.findVertex(nodeId);
        if (v == nullptr) {
            cerr << "\n\nThere is no such vertex in the city's graph\n\n";
        }

        vector<long> tasksIds;
        for (auto task: getTasks()) {
            tasksIds.push_back(task->getNodeId());
        }

        if (generalFunctions::inVector(tasksIds, nodeId)) {
            cerr << "\n\nThere is already a task in this vertex!\n\n";
            v = nullptr;
        }

    } while (v == nullptr);

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
    vector<Task*> t = getTasks();
    for (auto task: t) {
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

void Company::setBestPathToPickets() {
    vector<Picket*> p = getPickets(); // usa-se o método getPickets() e não pickets, para se poder limitar o seu número
    for (auto picket: p) {
        if (picket->getTasks().empty())
            continue;

        TSP<long> tsp(&cityGraph, searchAlgorithm);
        vector<long> path = tsp.calculatePath(picket->getTasksIds(), startVertexId, startVertexId);
        picket->setPath(path);

        picket->setCurrentTime(beginTime);

        for (auto nodeId: path) {
            if (generalFunctions::inVector<long>(picket->getTasksIds(), nodeId)) {
                Task* task = generalFunctions::getTaskById(nodeId, getTasks());
                Time currentTime = picket->getCurrentTime();
                task->setBeginTime(currentTime);
                currentTime = currentTime.addMinutes(task->getDurationMinutes()+1);
                picket->setCurrentTime(currentTime);
            }
        }
    }

}

void Company::setSearchAlgorithm(SEARCH_ALGORITHM searchAlgorithm) {
    this->searchAlgorithm = searchAlgorithm;
}

bool sortFunction(Picket *picket1, Picket *picket2) {
    if (picket1->getRoles().size() == picket2->getRoles().size()) {
        return picket1->getNumTasksDone() > picket2->getNumTasksDone();
    }
    return picket1->getRoles().size() > picket2->getRoles().size();
}

void Company::sortPicketsByNumTasksDone() {
    sort(pickets.begin(), pickets.end(), sortFunction);
}

void Company::limitNumTasks(int maxNumTasks) {
    this->maxNumTasks = maxNumTasks;
}

void Company::limitNumPickets(int maxNumPickets) {
    this->maxNumPickets = maxNumPickets;
}



