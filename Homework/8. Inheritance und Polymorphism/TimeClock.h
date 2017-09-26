//
// Created by CNESS on 4/21/2017.
//

#ifndef INC_8_INHERITANCE_UND_POLYMORPHISM_TIMECLOCK_H
#define INC_8_INHERITANCE_UND_POLYMORPHISM_TIMECLOCK_H

#include "MilTime.h"

class TimeClock : public MilTime {
private:
    int endHr, endSec;

public:

    // constructors
    TimeClock(){endHr = endSec = 0;}
    TimeClock(int startH, int startS, int endH, int endS);

    // destructors
    // accessors
    int getEndHr(){return endHr;}
    int getEndSec(){return endSec;}
    int TimeDifference();

    // mutators
    void setEndHr(int);
    void setEndSec(int);

};


#endif //INC_8_INHERITANCE_UND_POLYMORPHISM_TIMECLOCK_H
