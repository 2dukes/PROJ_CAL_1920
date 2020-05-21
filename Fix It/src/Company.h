//
// Created by Tiago on 12/05/2020.
//

#ifndef FIX_IT_COMPANY_H
#define FIX_IT_COMPANY_H

#include <vector>

#include "Picket.h"
#include "Task.h"
#include "Graph/Graph.h"

#define INF_NEG std::numeric_limits<double>::min()


using namespace std;

class Company {
    string name;
    vector<Picket*> pickets;
    vector<Task*> tasks;
    Graph<long int> cityGraph;
    Time beginTime;
    Time endTime;
    long startVertexId;

public:
    Company(string name);
    ~Company();
    string getName();
    Graph<long> &getCityGraph();
    bool readPicketsFile(const string& filename);
    bool readTasksFile(const string& filename);
    bool writePicketsFile(const string& filename);
    bool writeTasksFile(const string& filename);
    void addPicket(Picket* picket);
    void addTask(Task* task);
    vector<Picket*> getPickets();
    vector<Task*> getTasks();
    bool readNodes(const string &filename);
    bool readEdges(const string &filename);
    bool readCityGraph(const string &nodesFile, const string &edgesFile);
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
    Task* getTaskById(long vertexId);
};

template<class Type>
void Company::auxiliaryDestructor(vector<Type> &elements) {
    for(auto &x: elements)
        delete x;
}


#endif //FIX_IT_COMPANY_H
