#include "ConferenceTicket.hpp"
#include "Discounted.hpp"
#include "Taxed.hpp"
#include <iostream>

int main()
{
    Item item1(Taxed(0.15, Discounted(0.2, ConferenceTicket{"Core C++", 499.0})));

    const Money totalPrice1 = item1.price();

    std::cout << "Price for the book: " << totalPrice1.getAmount() << std::endl;
            
    return 0;
}