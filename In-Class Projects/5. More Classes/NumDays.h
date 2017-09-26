//
// Created by Connor on 4/18/2017.
//

#ifndef INC_5_MORE_CLASSES_NUMDAYS_H
#define INC_5_MORE_CLASSES_NUMDAYS_H

class NumDays {
private:
    float hours, days;
public:
    // constructors
    NumDays(){hours = 0, days = 0;}
    NumDays(float h){hours = h, days = h/8;}
    NumDays(const NumDays&);
    // accessors
    float getDays(){return days;}
    float getHours(){return hours;}
    int operator+(const NumDays& obj){return (int)(hours+obj.hours);}
    int operator-(const NumDays& obj){return (int)(hours-obj.hours);}
    bool operator<(const NumDays& obj){return (hours < obj.hours);}
    bool operator>(const NumDays& obj){return (hours > obj.hours);}

    // mutators
    void setDays(float d){days = d;}
    void setHours(float h){hours = h, days = hours/8;}
    NumDays& operator++();
    NumDays& operator++(int);

};


#endif //INC_5_MORE_CLASSES_NUMDAYS_H
