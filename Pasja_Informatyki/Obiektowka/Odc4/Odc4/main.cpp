#include "przyjaciele.h"

void sedzia(Punkt &pkt, Prostokat &p)
{
    if((pkt.x>=p.x)&&(pkt.x<=p.x+p.szerokosc)&&(pkt.y >=p.y)&&(pkt.y<=p.y+p.wysokosc))
    {
        std::cout << "Punkt " << pkt.nazwa << " nalezy do prostokata: " << p.nazwa << std::endl;
    }
    else
    {
        std::cout << "Punkt " << pkt.nazwa << " lezy POZA prostokatem: " << p.nazwa << std::endl;
    }
}

int main()
{
    Punkt pkt1("A", 3, 17);
    //pkt1.wczytaj();

    Prostokat p1("Prostokat", 0, 0, 6, 4);
    //p1.wczytaj();

    sedzia(pkt1, p1);

    return 0;
}
