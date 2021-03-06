//
// Created by Tiago on 12/05/2020.
//

#ifndef FIX_IT_COMPANY_H
#define FIX_IT_COMPANY_H

#include <vector>

#include "Picket.h"
#include "Task.h"
#include "Graph/Graph.h"
#include "Algorithms/TSP.h"

enum CITY {Porto = 1, Penafiel = 2, Espinho = 3, PortoFull = 4, PenafielFull = 5, EspinhoFull = 6};

using namespace std;

class Company {
    string name;                            // Nome da empresa

    vector<Picket*> pickets;                // Lista Pickets

    vector<Task*> tasks;                    // Lista de tasks

    Graph<long int> cityGraph;              // Grafo utilizado

    Time beginTime;                         // Horário de trabalho - Início

    Time endTime;                           // Horário de trabalho - Fim

    long startVertexId;                     // Nó que representa a empresa

    SEARCH_ALGORITHM searchAlgorithm;       // Algoritmo de procura a ser utilizado

    int maxNumTasks = INT32_MAX;            // Máximo número de tasks

    int maxNumPickets = INT32_MAX;          // Máximo número de Pickets

public:
    Company(string name, CITY cityNum);
    ~Company();
    string getName();
    Graph<long> &getCityGraph();
    bool readPicketsFile(const string& filename);
    bool readTasksFile(const string& filename);
    bool writePicketsFile(const string& filename);
    bool writeTasksFile(const string& filename);
    void addPicket(Picket* picket);
    void addTask(Task* task);
    vector<Picket*> getPickets() const;
    vector<Task*> getTasks() const;
    bool readNodes(const string &filename);
    bool readEdges(const string &filename);
    void readCityGraph(const string &nodesFile, const string &edgesFile);
    void setZonesToTasks();
    template<class Type>
    void auxiliaryDestructor(vector<Type> &elements);
    void showPicketsInfo() const;
    void showTasksInfo() const;
    bool createPicket();
    bool createTask();
    Time getBeginTime() const;
    Time getEndTime() const;
    void setBeginTime(const Time &time);
    void setEndTime(const Time &time);
    long getStartVertexId() const;
    void setStartVertexId(long vertexId);
    void setRandomNodesToTasks();
    void setBestPathToPickets();
    void setSearchAlgorithm(SEARCH_ALGORITHM searchAlgorithm);
    void sortPicketsByNumTasksDone();
    void limitNumTasks(int maxNumTasks);
    void limitNumPickets(int maxNumPickets);
    void deleteUnusefulNodes(vector<long>& SCCTree);
};

template<class Type>
void Company::auxiliaryDestructor(vector<Type> &elements) {
    for(auto &x: elements)
        delete x;
}


#endif //FIX_IT_COMPANY_H
