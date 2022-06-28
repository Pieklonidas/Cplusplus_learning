#include <iostream>
#include <math.h>

class Punkt
{
    float x,y;
    std::string nazwa;
public:
    void wyswietl()
    {
        std::cout << nazwa << "(" << x << "," << y << ")" << std::endl;
    }
    Punkt(std::string n="S", float a=0.f, float b=0.f)
    {
        nazwa = n;
        x = a;
        y = b;
    }
};

class Kolo : public Punkt //klasa kolo dziedziczy publicznie z klasy Punkt
{

    std::string nazwa;
protected:
    float r;
public:
    void wyswietl()
    {
        std::cout << "Kolo o nazwie: " << nazwa << std::endl;
        std::cout << "Srodek kola: " << std::endl;
        Punkt::wyswietl();
        std::cout << "Promien: " << r << std::endl;
        std::cout << "Pole kola: " << M_PI*r*r << std::endl;
    }

    Kolo(std::string nk="Kolko", std::string np="S", float a=0.f, float b=0.f, float pr=1.f)
        : Punkt(np, a, b)
    {
        nazwa = nk;
        r = pr;
    }
};

class Kula : public Kolo
{
    std::string nazwa;
public:
    void wyswietl()
    {
        std::cout << "Kula o nazwie: " << nazwa << std::endl;
        std::cout << "Srodek kuli: ";
        Punkt::wyswietl();
        std::cout << "Promien: " << r << std::endl;
        std::cout << "Objetosc kuli: " << 4.f/3.f*M_PI*r*r*r << std::endl;
    }

    Kula(std::string nku="Kulka", std::string nk="Kolko", std::string np="S", float a=0.f, float b=0.f, float pr=1.f)
        : Kolo(nk, np, a, b, pr)
    {
        nazwa = nku;
    }
};

int main()
{
    Kolo k1;
    k1.wyswietl();
    Kula k2("Kula", "Kolo", "Punkt", 2.f, 2.f, 2.f);
    k2.wyswietl();
    std::cout << M_PI << std::endl;
    return 0;
}
