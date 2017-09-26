#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include "Employee.h"

class Supervisor : public Employee
{
protected:
    float bonus;

public:
    Supervisor(){ bonus = 0.0;}
    Supervisor(char*, int, double, string, float);
    float getBonus() { return bonus;}
    void setBonus(float b) { bonus = b;}

    virtual float getSalary() const { return salary + bonus;}


};
#endif // SUPERVISOR_H
