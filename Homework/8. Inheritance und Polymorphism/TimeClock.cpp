//
// Created by CNESS on 4/21/2017.
//

#include "TimeClock.h"

// constructors
TimeClock::TimeClock(int startH, int startS, int endH, int endS) : MilTime(startH, startS) {
    setEndHr(endH);
    setEndSec(endS);
}

// destructors
// accessors
int TimeClock::TimeDifference() {
    int endMinutes = (endHr-((endHr/100)*100));
    int endHours = ((endHr/100)*100);
    int begHours = ((MilTime::getMilHours()/100)*100);
    int begMinutes = (MilTime::getMilHours()-((MilTime::getMilHours()/100)*100));
    if(endHours < begHours) {
        int temp = endHours;
        endHours = begHours;
        begHours = temp;
        temp = endMinutes;
        endMinutes = begMinutes;
        begMinutes = temp;
    }

    if(endMinutes < begMinutes) {
        endMinutes = ((60+endMinutes) - begMinutes);
        endHours -= 100;
    }
    else {
        endMinutes -= begMinutes;
    }
    endHours -= begHours;

    return endHours + endMinutes;
}

// mutators
void TimeClock::setEndHr(int endH) {
    int endM = (endH-((endH/100)*100));
    if(endH >= 2400)
        endH = 2359;
    if(endM > 59 && endM < 80)
        endH = (endH - endM + 59);
    else if(endM > 79)
        endH = (endH - endM + 100);
    if(endH >= 2400)
        endH = 2359;
    else if(endH < 0)
        endH = 0;

    endHr = endH;
}

void TimeClock::setEndSec(int endS) {
    if(endS > 59) {
        if(endS < 80)
            endS = 59;
        else
            endS = 0;
    }
    else if(endS < 0)
        endS = 0;
    endSec = endS;
}