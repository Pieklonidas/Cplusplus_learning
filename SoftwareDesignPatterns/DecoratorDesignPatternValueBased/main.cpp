#include "ConferenceTicket.hpp"
#include "Discounted.hpp"
#include "Taxed.hpp"
#include <cstdlib>
#include <iostream>

int main()
{
    Taxed<0.15, Discounted<0.2, ConferenceTicket>> item1{ "Core C++", 499.0 };

    const Money totalPrice1 = item1.price();

    std::cout << "Price for the ticket: " << totalPrice1.getAmount() << std::endl;
            
    return 0;
}