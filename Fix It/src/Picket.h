#ifndef FIX_IT_PICKET_H
#define FIX_IT_PICKET_H

#include <string>
#include <vector>
#include "Task.h"
#include "Utils/Time.h"

using namespace std;

class Task;

class Picket {

    static int current_id; // Last inserted ID

    int id;                // Picket ID

    string name;           // Picket Name

    vector<string> roles;  // Skills

    vector<Task*> tasks;   // Assigned Tasks

    int zone;              // Zone where it belongs

    int numTasksDone;      // Number of previous tasks done (experience)

    vector<long> path;     // Path to wander

    Time currentTime;      // Last task Time


public:
    Picket(string name, vector<string> roles, int numTasksDone);
    int getId() const;
    string getName() const;
    vector<string> getRoles() const;
    bool verifyRole(const string &role) const;
    void setName(const string &name);
    void setRoles(const vector<string> &roles);
    void addRole(const string &role);
    bool removeRole(const string &role); // true se removeu, false se não existia
    bool timeIsCompatible(const Time &time1, const Time &time2) const;
    bool addTask(Task *task);
    vector<Task*> getTasks() const;
    vector<long> getTasksIds() const;
    int getNumTasksDone() const;
    friend ostream& operator<<(ostream& os, const Picket &picket);
    void setZone(int zone);
    int getZone() const;
    void setPath(vector<long> path);
    void addToPath(long nodeId);
    vector<long> getPath() const;
    void setCurrentTime(const Time &time);
    Time getCurrentTime() const;
    void clearTasks();
};


#endif //FIX_IT_PICKET_H
