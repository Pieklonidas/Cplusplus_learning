#pragma once

#include "Observer.hpp"
#include "Person.hpp"

class AddressObserver : public Observer<Person, Person::StateChange>
{
public:
    void update(const Person& person, Person::StateChange property) override;
};