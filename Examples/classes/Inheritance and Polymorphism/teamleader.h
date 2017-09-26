
#ifndef TEAMLEADER_H
#define TEAMLEADER_H
#include "Supervisor.h"

class TeamLeader : public Supervisor
{
protected:
    int hours;
    float rate;

public:
    TeamLeader();
    TeamLeader(char*, int, string, float, int, float);
    virtual float getSalary() const {return rate * hours * 52;}

};
#endif // TEAMLEADER_H
