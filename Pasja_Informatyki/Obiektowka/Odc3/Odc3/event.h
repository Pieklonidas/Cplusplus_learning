#ifndef EVENT_H
#define EVENT_H
#include <iostream>

class Event
{
private:
    int day, month, year;
    int hour, minutes;
    std::string name;

public:
    Event(std::string="brak", int=1, int=1, int=2015, int=12, int=0);
    ~Event();
    void load();
    void show();
};

#endif // EVENT_H
