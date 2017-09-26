#include "Supervisor.h"


Supervisor::Supervisor(char* n, int id, double s, string d, float b) : Employee(n, id, s, d)
{
    bonus = b;
}
