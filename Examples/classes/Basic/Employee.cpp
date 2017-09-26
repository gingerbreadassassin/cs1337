#include "Employee.h"
#include <cstring>

/*void*/ Employee::Employee()
{
    department = new char[20];
    department[0] = '\0';
    //or *department = '\0';
}

/*void */ Employee::Employee(string n, char* dept, int id, double sal)
{
    name = n;
    salary = sal;
    ID = id;
    //department = dept;  DON'T DO THIS
    department = new char[20];
    strncpy(department, dept, 20);
}

void Employee::setDepartment(char* d)
{
    strncpy(department, d, 20);
    //remember strncpy does not auto add null terminator
    department[19] = '\0';
}
