#include "event.h"

void Event::load()
{
    std::cout << std::endl << "Nazwa wydarzenia: ";
    std::cin >> name;
    std::cout << std::endl << "Dzień: ";
    std::cin >> day;
    std::cout << std::endl << "Miesiąc: ";
    std::cin >> month;
    std::cout << std::endl << "Rok: ";
    std::cin >> year;
    std::cout << std::endl << "Godzina: ";
    std::cin >> hour;
    std::cout << std::endl << "Minuta: ";
    std::cin >> minutes;
}

void Event::show()
{
    std::cout << name << " " << day << "." << month << "." << year << " " << hour << ":" << minutes <<std::endl;
}

Event::Event(std::string n, int d, int m, int y, int h, int mins)
{
    name = n;
    day = d;
    month = m;
    year = y;
    hour = h;
    minutes = mins;
}

Event::~Event()
{
    std::cout << "To ja destruktor" << std::endl;
}
