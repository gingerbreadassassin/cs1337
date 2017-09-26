#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
using namespace std;

class Employee
{
private:
    string name;
    char* department;
    int ID = 0;
    double salary = 0;

public:
    //constructors
    Employee();
    Employee(string, char*, int, double);

    //destructor
    ~Employee() {delete [] department;}


    // accessors
    int getID() const {return ID;}
    string getName() const {return name;}  //inline function
    double getSalary() const {return salary;}
    const char* getDepartment() const {return department;}

    //mutators
    void setName(string n) {name = n;}
    void setID(int id) {ID = id;}
    void setSalary(double s) {salary = s;}
    void setDepartment(char* d);
};

#endif // EMPLOYEE_H
