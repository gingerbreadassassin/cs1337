//
// Created by CNESS on 4/21/2017.
//

#ifndef INC_8_INHERITANCE_UND_POLYMORPHISM_MILTIME_H
#define INC_8_INHERITANCE_UND_POLYMORPHISM_MILTIME_H

#include "Time.h"

class MilTime : public Time {
private:
    int milHours;

public:

    // constructors
    MilTime(){milHours = 0;}
    MilTime(int h, int s){setTime(h, s);}
    // destructors
    // accessors
    int getMilHours(){return milHours;}
    int getStandHr(){return Time::getHours();}
    // mutators
    void setMilHours(int);
    void setTime(int, int);


};


#endif //INC_8_INHERITANCE_UND_POLYMORPHISM_MILTIME_H
