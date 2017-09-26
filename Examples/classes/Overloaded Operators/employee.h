#ifndef EMPLOYEE_H
#define EMPLOYEE_H


#include <string>
#include <cstring>
#include <iostream>
using namespace std;

//class Employee; //forward declaration
//ostream& operator<<(ostream&, const Employee&);
//istream& operator>>(istream&, const Employee&);

class Employee
{
protected:
    string name;
    int ID;
    float salary;
    char* department;
    static int Empnum;

public:


    //constructors
    Employee(); //default constructor
    Employee(string, int, float, char*);    //overloaded constructor
    Employee(const Employee &);   //copy constructor

    //destructor
    ~Employee()
        {  delete [] department; Empnum--;   }


    //accessors
    static int getEmpnum()
    {  return Empnum;    }

    string getName() const
    {   return name;   }

    int getID() const
    {   return ID;   }

    float getSalary() const
    {   return salary;   }

    const char* getDepartment() const
    {   return department;   }

    //mutators
    void setName(string s)
    {   name = s;  }  //inline function

    void setID(int id)
    {   ID = id;  }

    void setSalary(float s)
    {   salary = s;  }

    void setDepartment(char* d)
    {   strncpy(department, d, 29); department[29] = '\0'; }

    //overloaded operators
    Employee operator=(const Employee &);

    friend ostream& operator<<(ostream&, const Employee&);
    friend istream& operator>>(istream&, Employee&);

};
#endif // EMPLOYEE_H
