#include <iostream>
#include "Person.hpp"
#include "NameObserver.hpp"
#include "AddressObserver.hpp"
#include <cstdlib>

int main()
{
    NameObserver nameObserver;
    AddressObserver addressObserver;

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