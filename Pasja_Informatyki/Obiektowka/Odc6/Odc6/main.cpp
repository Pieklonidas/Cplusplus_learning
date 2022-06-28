#include <iostream>

class Ksztalt
{
public:
    virtual void oblicz_pole() = 0; // czysta funkcja wirutalna
};

class Kolo : public Ksztalt
{
    float r;
public:
    Kolo (float x)
    {
        r = x;
    }
    virtual void oblicz_pole()
    {
        std::cout << "Pole kola: " << 3.14*r*r << std::endl;
    }
};

class Kwadrat : public Ksztalt
{
    float a;
public:
    Kwadrat (float x)
    {
        a = x;
    }
    virtual void oblicz_pole()
    {
        std::cout << "Pole kwadratu: " << a*a << std::endl;
    }
};

void obliczenia(Ksztalt* x)
{
    x -> oblicz_pole();
}

int main()
{
    Kolo k(1.f);
    Kwadrat kw(2.f);

    Ksztalt *wsk;
    wsk = &k;
    wsk -> oblicz_pole();

    wsk = &kw;
    wsk -> oblicz_pole();

    obliczenia(wsk);

    return 0;
}
