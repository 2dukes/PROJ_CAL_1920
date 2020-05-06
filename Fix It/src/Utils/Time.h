//
// Created by Tiago on 06/05/2020.
//

#ifndef FIX_IT_TIME_H
#define FIX_IT_TIME_H

#include <string>

using namespace std;

class Time {
    int minutes;
    int hours;

public:
    Time(int hours, int minutes);
    Time(const string &time);
    int getMinutes();
    int getHours();
};


#endif //FIX_IT_TIME_H
