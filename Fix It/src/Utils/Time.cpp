//
// Created by Tiago on 06/05/2020.
//

#include <iostream>
#include <sstream>
#include "Time.h"

Time::Time(int hours, int minutes) {
    if (hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60) {
        this->hours = hours;
        this->minutes = minutes;
    }
    else {
        cerr << "Invalid Time!" << endl;
    }
}

Time::Time(const string &time) {
    int hours, minutes;
    if (sscanf(time.c_str(), "%d:%d", &hours, &minutes) != 2) {
        cerr << "Invalid Time!" << endl;
    }
    else {
        new (this) Time(hours, minutes);
    }
}

int Time::getMinutes() {
    return minutes;
}

int Time::getHours() {
    return hours;
}
