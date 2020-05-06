//
// Created by Tiago on 06/05/2020.
//

#ifndef FIX_IT_PICKET_H
#define FIX_IT_PICKET_H

#include <string>

using namespace std;

class Picket {
    static int current_id;
    int id;
    string name;
    string role;

public:
    Picket(string name, string role);
    int getId();
    string getName();
    string getRole();
    void setName(string &name);
    void setRole(string &role);
};


#endif //FIX_IT_PICKET_H
