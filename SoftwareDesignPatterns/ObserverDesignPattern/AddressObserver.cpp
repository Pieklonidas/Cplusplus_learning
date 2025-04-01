#include "AddressObserver.hpp"
#include <iostream>

void AddressObserver::update(const Person& person, Person::StateChange property)
{
    if(property == Person::addressChanged)
    {
        std::cout << "address changed for:" << std::endl;
        std::cout << person.forename() << " " << person.surname() << std::endl;
        std::cout << "new address:" << std::endl;
        std::cout << person.address() << std::endl;
    }
}