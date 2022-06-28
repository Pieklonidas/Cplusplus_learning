#include "pytanie.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

void pytanie::wczytaj()
{
    std::fstream plik;
    plik.open("quiz.txt", std::ios::in);

    if(plik.good() == false)
    {
        std::cout << "Nie udalo sie otworzyc pliku" << "\n";
        exit(0);
    }

    int nr_linii = (nr_pytania-1)*6+1;
    int aktualny_nr = 1;
    std::string linia;

    while (std::getline(plik,linia))
    {
        if(aktualny_nr == nr_linii) tresc = linia;
        if(aktualny_nr == nr_linii+1) a = linia;
        if(aktualny_nr == nr_linii+2) b = linia;
        if(aktualny_nr == nr_linii+3) c = linia;
        if(aktualny_nr == nr_linii+4) d = linia;
        if(aktualny_nr == nr_linii+5) poprawna  = linia;

        aktualny_nr++;
    }
    plik.close();
}

void pytanie::zadaj()
{
    std::cout << "\n" << tresc << "\n";
    std::cout << a << "\n";
    std::cout << b << "\n";
    std::cout << c << "\n";
    std::cout << d << "\n";
    std::cout << "\nOdpowiedz\n";
    std::cin >> odpowiedz;
    odpowiedz[0] = std::tolower(odpowiedz[0]);
}

void pytanie::sprawdz()
{
    if(odpowiedz == poprawna)
    {
        punkt = 1;
    }
    else punkt=0;
}
