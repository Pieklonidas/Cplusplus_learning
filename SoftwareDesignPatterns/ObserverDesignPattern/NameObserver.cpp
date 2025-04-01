#include "NameObserver.hpp"
#include <iostream>

void NameObserver::update(const Person& person, Person::StateChange property)
{
    if(property == Person::forenameChanged || property == Person::surnameChanged)
    {
        std::cout << "forename or surname changed to:" << std::endl;
        std::cout << person.forename() << " " << person.surname() << std::endl;
    }
}