#ifndef PRZYJACIELE_H
#define PRZYJACIELE_H
#include <iostream>

class Prostokat;

class Punkt
{
    std::string nazwa;
    float x,y;
public:
    Punkt(std::string="A", float=0.f, float=0.f);
    void wczytaj();

    friend void sedzia(Punkt &pkt, Prostokat &p);
};

class Prostokat
{
    std::string nazwa;
    float x,y,szerokosc,wysokosc;
public:
    Prostokat(std::string="brak", float=0.f, float=0.f, float=1.f, float=1.f);
    void wczytaj();

    friend void sedzia(Punkt &pkt, Prostokat &p);
};

#endif // PRZYJACIELE_H
