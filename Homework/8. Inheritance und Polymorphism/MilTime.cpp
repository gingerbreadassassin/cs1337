//
// Created by CNESS on 4/21/2017.
//

#include "MilTime.h"

// constructors
// destructors
// accessors

// mutators
void MilTime::setMilHours(int h) {
    int m = (h-((h/100)*100));
    if(m > 59) {
        if(m > 59 && m < 80)
            h = (h - m + 59);
        else if(m > 79)
            h = (h - m + 100);
        if(h >= 2400) {
            h = 2359;
            m = 59;
        }
    }
    if((h/100) > 12)
        Time::setHours((h/100)-12);
    else if((h/100) == 0)
        Time::setHours(12);
    else
        Time::setHours(h/100);
    Time::setMinutes(m);
    milHours = h;
}

void MilTime::setTime(int h, int s) {
    setMilHours(h);
    if(s > 59) {
        if(s < 80)
            s = 59;
        else
            s = 0;
    }
    else if(s < 0)
        s = 0;
    Time::setSeconds(s);
}