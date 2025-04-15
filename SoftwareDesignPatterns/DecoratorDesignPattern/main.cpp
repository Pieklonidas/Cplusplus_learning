#include "ConferenceTicket.hpp"
#include "CppBook.hpp"
#include "Discounted.hpp"
#include "Taxed.hpp"
#include <cstdlib>
#include <memory>
#include <iostream>

int main()
{
    std::unique_ptr<Item> item1(
        std::make_unique<Taxed>( 0.07,
            std::make_unique<CppBook>("Effective C++", 19.0) ) );
    
    std::unique_ptr<Item> item2(
        std::make_unique<Taxed>( 0.19,
            std::make_unique<Discounted>( 0.2,
                std::make_unique<ConferenceTicket>("CppCon", 999.0) ) ) );

    const Money totalPrice1 = item1->price();
    const Money totalPrice2 = item2->price();

    std::cout << "Price for the book: " << totalPrice1.getAmount() << std::endl;
    std::cout << "Price for the ticket: " << totalPrice2.getAmount() << std::endl;
            
    return 0;
}