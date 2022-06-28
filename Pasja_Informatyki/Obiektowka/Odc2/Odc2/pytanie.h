#ifndef PYTANIE_H
#define PYTANIE_H

#include <iostream>

class pytanie
{
public:
    std::string tresc;
    std::string a,b,c,d;
    int nr_pytania;
    std::string poprawna;
    std::string odpowiedz;
    int punkt;

    void wczytaj(); // wczytuje pytania z pliku
    void zadaj();
    void sprawdz();
};

#endif // PYTANIE_H
