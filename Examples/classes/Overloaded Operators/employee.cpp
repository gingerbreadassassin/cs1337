
#include "employee.h"

int Employee::Empnum = 0;

/*no return*/ Employee::Employee()
{
    //name = "";
    ID = 0;
    salary = 0.00;
    department = new char[30];
    *department = '\0';
    //department[0] = '\0';
    //strcpy(department, "");
    Empnum++;
}

Employee::Employee(string n, int id, float s, char* d)
{
    name = n;
    ID = id;
    salary = s;
    department = new char[30];
    strncpy(department, d, 29);
    department[29] = '\0';
    Empnum++;
}

Employee::Employee(const Employee &obj)
{
    name = obj.name;
    ID = obj.ID;
    salary = obj.salary;
    department = new char[30];
    strncpy(department, obj.department, 29);
    department[29] = '\0';
    Empnum++;
}

Employee Employee::operator=(const Employee &obj)
{
    name = obj.name;
    ID = obj.ID;
    salary = obj.salary;
    strncpy(department, obj.department, 29);
    department[29] = '\0';
    return *this;
}

/*Employee Employee::operator++(int)
{
    Employee temp = *this;
    salary += 2000;
    return temp;
}*/

ostream& operator<<(ostream& out, const Employee& obj)
{
    out << " Employee name: " << obj.name << endl;
    out << " Employee salary: " << obj.salary << endl;
    out << " Employee ID: " << obj.ID << endl;
    out << " Employee department: " << obj.department << endl<<endl;
    return out;
}

istream& operator>>(istream& in, Employee& obj)
{
    cout << "Enter Employee name: ";
    in >> obj.name;
    cout << "Enter Employee salary: ";
    in >> obj.salary;
    cout << "Enter Employee ID: ";
    in >> obj.ID;
    cout << "Enter Employee department: ";
    in >> obj.department;

    return in;
}
