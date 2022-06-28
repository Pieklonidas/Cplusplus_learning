#include <iostream>

class Zwierze
{
public:
    // atrybuty
    std::string gatunek;
    std::string imie;
    int wiek;

    //metody
    void dodaj_zwierze()
    {
        std::cout << "DODAWANIE NOWEGO ZWIERZECIA DO BAZY: " << std::endl;
        std::cout << "Podaj gatunek: ";
        std::cin >> gatunek;
        std::cout << "Podaj imie: ";
        std::cin >> imie;
        std::cout << "Podaj wiek: ";
        std::cin >> wiek;
    }

    void daj_glos()
    {
        if(gatunek == "kot") std::cout << imie << " lat: " << wiek <<": Miau!\n";
        else if(gatunek == "koza") std::cout << imie << " lat: " << wiek <<": Beee!\n";
        else if(gatunek == "krowa") std::cout << imie << " lat: " << wiek <<": Muuu!\n";
        else std::cout << "Nieznany gatunek";
    }
};

class Samochod
{
public:
    // atrybuty
    std::string marka;
    std::string model;
    int rocznik;
    int przebieg;

    //metody
    void wczytaj()
    {
        std::cout << "DODAWANIE NOWEGO SAMOCHODU DO BAZY: " << std::endl;
        std::cout << "Podaj marke: ";
        std::cin >> marka;
        std::cout << "Podaj model: ";
        std::cin >> model;
        std::cout << "Podaj rocznik: ";
        std::cin >> rocznik;
        std::cout << "Podaj przebieg: ";
        std::cin >> przebieg;
    }

    void wypisz()
    {
        std::cout << "Marka: " << marka << "\nModel: " << model << "\nRocznik: " << rocznik << "\nPrzebieg: " << przebieg << "\n";
    }
};

int main()
{
    Zwierze z1;

    z1.dodaj_zwierze();
    z1.daj_glos();

    Zwierze z2;
    z2.dodaj_zwierze();
    z2.daj_glos();

    Samochod s1;
    s1.wczytaj();
    s1.wypisz();

    Samochod s2;
    s2.wczytaj();
    s2.wypisz();

    return 0;
}
