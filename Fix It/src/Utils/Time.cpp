//
// Created by Tiago on 06/05/2020.
//

#include <iostream>
#include <sstream>
#include "Time.h"

Time::Time() {
    hours = 0;
    minutes = 0;
}

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

int Time::getMinutes() const {
    return minutes;
}

int Time::getHours() const {
    return hours;
}

bool Time::operator<(const Time &time) const {
    if (hours == time.getHours())
        return minutes < time.getMinutes();
    return hours < time.getHours();
}

bool Time::operator==(const Time &time) const {
    return hours == time.getHours() && minutes == time.getMinutes();
}

Time Time::getTimeInterval(const Time &time1) const {
    if (*this < time1) {
        int numMinutes = time1.getHours() * 60 + time1.getMinutes() - hours * 60 - minutes;
        return {numMinutes / 60, numMinutes % 60};
    }
    else if (time1 < *this) {
        int numMinutes = hours * 60 + minutes - time1.getHours() * 60 - time1.getMinutes();
        return {numMinutes / 60, numMinutes % 60};
    }
    return {0, 0};
}


