#include "teamleader.h"

TeamLeader::TeamLeader()
{
    hours = 0;
    rate = 0.0;
}

TeamLeader::TeamLeader(char* n, int id, string d, float b, int h, float r) : Supervisor (n, id, 0, d, b)
{
    hours = h;
    rate = r;
}
