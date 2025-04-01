#include <iostream>
#include "Person.hpp"
#include "Observer.hpp"
#include <cstdlib>

void propertyChanged(const Person& person, Person::StateChange property)
{
    if(property == Person::forenameChanged || property == Person::surnameChanged)
    {
        std::cout << "forename or surname changed to:" << std::endl;
        std::cout << person.forename() << " " << person.surname() << std::endl;
    }
}

int main()
{
    using PersonObserver = Observer<Person, Person::StateChange>;

    PersonObserver nameObserver(propertyChanged);

    PersonObserver addressObserver(
        [](const Person& person, Person::StateChange property)
        {
            if(property == Person::addressChanged)
            {
                std::cout << "address changed for:" << std::endl;
                std::cout << person.forename() << " " << person.surname() << std::endl;
                std::cout << "new address:" << std::endl;
                std::cout << person.address() << std::endl;
            }
        }
    );

    Person homer("Homer", "Simpson");
    Person marge("Marge", "Simpson");
    Person monty("Montgomery", "Burns");
    
    homer.attach(&nameObserver);
    marge.attach(&nameObserver);
    marge.attach(&addressObserver);
    monty.attach(&addressObserver);

    homer.forename("Homer Jay");
    homer.address("New Address");

    marge.address("712 Red Bark Lane, Henderson, Clark County, Nevada 89011");
    marge.surname("Married");

    monty.address("Springfield Nuclear Power Plant");

    marge.dettach( &addressObserver );

    marge.address("Rokoko");

    return 0;
}