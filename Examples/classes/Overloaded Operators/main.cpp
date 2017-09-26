#include "Employee.h"
#include <iostream>
using namespace std;

void fillEmployee(Employee& obj, char* n, int i, float s, char* d)
{
    obj.setID(i);
    obj.setName(n);
    obj.setSalary(s);
    obj.setDepartment(d);

}

int main()
{
    cout << "Num Employees: " << Employee::getEmpnum()<< endl;
    Employee E1;
    cout << E1 << endl << endl;

    Employee E2("Jane Doe", 54321, 50000, "IT");
    Employee E2A;
    E2A = E1 = E2;

    E2A.setName("Jake Doe");
    E2A.setDepartment("Insurance");
    cout << E2 << endl << endl;
    cout << E2A << endl << endl;


    Employee *E3 = new Employee;
    cout << *E3 << endl << endl;

    Employee *E4 = new Employee("Jane Doe", 4321, 45000, "IT");
    cout << *E4 << endl << endl;

cout << "Num Employees: " << Employee::getEmpnum()<< endl;

    //dynamic array of objects
    Employee *EArray = new Employee[5];
    for (int i = 0; i < 5; i++)
        //workaround for overloaded constructor
        fillEmployee(EArray[i], "name", 6789, 50000, "IT");

cout << "Num Employees: " << Employee::getEmpnum()<< endl;

    //dynamic array of dynamic objects
    Employee **EArray2 = new Employee*[5];
    for (int i = 0; i < 5; i++)
        EArray2[i] = new Employee;

cout << "Num Employees: " << Employee::getEmpnum()<< endl;

    for (int i = 0; i < 5; i++)
        cout << EArray[i].getID() << " ";
    cout << endl;

    for (int i = 0; i < 5; i++)
        cout << EArray2[i]->getID() << " ";
    cout << endl;



    delete E3;
    delete E4;

cout << "Num Employees: " << Employee::getEmpnum()<< endl;

    delete [] EArray;

cout << "Num Employees: " << Employee::getEmpnum()<< endl;

    for (int i = 0; i < 5; i++)
    {
        delete EArray2[i];
        cout << "Num Employees: " << Employee::getEmpnum()<< endl;
    }
    delete [] EArray2;

cout << "Num Employees: " << Employee::getEmpnum()<< endl;

    return 0;
}

