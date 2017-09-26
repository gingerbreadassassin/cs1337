//
// Created by Connor on 4/18/2017.
//

#include "NumDays.h"

// constructors
NumDays::NumDays(const NumDays& obj){
    hours = obj.hours;
    days = obj.days;
}


// mutators
NumDays & NumDays::operator++(){
    hours++;
    days = hours/8;
    return *this;
}

NumDays & NumDays::operator++(int) {
    NumDays temp = *this;
    hours++;
    days = hours/8;
    return temp;
}
