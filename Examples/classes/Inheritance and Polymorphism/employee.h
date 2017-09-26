
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <cstring>
#include <fstream>
using namespace std;

class Employee;

ostream& operator <<(ostream&, const Employee&);
istream& operator >>(istream&, Employee&);

class Employee
{
protected:
    char* name;
    int ID;
    double salary;
    string department;
    static int numEmp;

public:
    Employee();
    Employee(char*, int, double, string);
    Employee(const Employee&);
    ~Employee();

    Employee operator=(const Employee&);
    Employee operator++(); //prefix
    Employee operator++(int);  //postfix


    static int getEmpnum()
    {   return numEmp;    }

    void setID(int id)
    { ID = id; }

    int getID() const
    { return ID;    }

    void setName(char * n)
    {   strncpy(name, n, 20);   name[19] = '\0';    }

    const char * getName() const
    {   return name;    }

    void setSalary(float s)
    {   salary = s;    }

    virtual float getSalary() const
    {   return salary;    }

    void setDepartment(string d)
    {   department = d;    }

    string getDept() const
    {   return department;  }

    friend ostream& operator <<(ostream&, const Employee&);
    friend istream& operator >>(istream&, Employee&);
};

#endif // EMPLOYEE_H
