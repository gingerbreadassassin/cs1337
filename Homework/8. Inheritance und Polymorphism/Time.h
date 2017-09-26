#ifndef TIME_H
#define TIME_H

class Time
{
private:
    int hours=0;
    int minutes=0;
    int seconds=0;

public:
    Time(){hours = minutes = seconds = 0;}
    Time(int h, int m, int s)
    {hours=h; minutes=m; seconds=s;}

    int getHours() {return hours;}
    int getMinutes() {return minutes;}
    int getSeconds() {return seconds;}

    void setHours(int h) {hours=h;}
    void setMinutes(int m) {minutes=m;}
    void setSeconds(int s) {seconds=s;}
};
#endif // TIME_H
