#include "Employee.h"
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

int Employee::numEmp = 0;


Employee::Employee()
{
    name = new char[20];
    ID = 0;
    salary = 0;
    strcpy(name, "\0");
    department = "";
    numEmp++;

}

Employee::Employee(char* n, int id, double s, string d)
{
    name = new char[20];
    ID = id;
    salary = s;
    strncpy(name, n, 19);
    name[19]= '\0';
    department = d;
    numEmp++;
}

Employee::Employee(const Employee &obj)
{
    name = new char[20];
    ID = obj.ID;
    salary = obj.salary;
    strcpy(name, obj.name);
    //name[19]= '\0';
    department = obj.department;
    numEmp++;
}

Employee::~Employee()
{
    cout << "Object Name: " << name << endl;
    delete [] name;
    numEmp--;
}

Employee Employee::operator=(const Employee& obj)
{
    ID = obj.ID;
    salary = obj.salary;
    strcpy(name, obj.name);
    department = obj.department;
    return *this;
}

//prefix notation
Employee Employee::operator++()
{
    salary += 1000;
    return *this;
}

//postfix notation
Employee Employee::operator++(int)
{
    Employee temp = *this;
    salary += 1000;
    return temp;
}

ostream& operator << (ostream& str, const Employee &obj)
{

    str << "Name: " << obj.name << "\nID: " << obj.ID << "\nSalary: " << obj.getSalary() << "\nDepartment: " << obj.department << endl << endl;
    return str;
}

istream& operator >>(istream& str, Employee& obj)
{
    cout << "Please enter the name: ";
    string name;
    getline(cin, name);
    strncpy(obj.name, name.c_str(), 20);
    obj.name[name.length()] = '\0';

    cout << "Please enter the ID: ";
    cin >> obj.ID;

    cout << "Please enter the salary: ";
    cin >> obj.salary;

    cout << "Please enter the department: ";
    getline(cin, obj.department);

    return str;
}





