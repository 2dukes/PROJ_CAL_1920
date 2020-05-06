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
    Time();
    Time(int hours, int minutes);
    Time(const string &time);
    int getMinutes() const;
    int getHours() const;
    bool operator<(const Time &time) const;
    bool operator==(const Time &time) const;
    Time getTimeInterval(const Time &time1) const; // Time inverval between 2 times on the same day
    bool checkTimeOverlap(const Time &time1, const Time &time2) const; // check if *this is between time1 and time2
};


#endif //FIX_IT_TIME_H
