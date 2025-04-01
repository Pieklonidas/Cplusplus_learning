#include "Person.hpp"

bool Person::attach(PersonObserver* observer)
{
    auto [_, success] = observers_.insert(observer);
    return success;
}

bool Person::dettach(PersonObserver* observer)
{
    return (observers_.erase(observer) > 0U);
}

void Person::notify(StateChange property)
{
    for(auto iter = begin(observers_); iter != end(observers_);)
    {
        auto const pos = iter++;
        (*pos)->update(*this, property);
    }
}

void Person::forename(std::string newForename)
{
    forename_ = std::move(newForename);
    notify(forenameChanged);
}

void Person::surname(std::string newSurname)
{
    surname_ = std::move(newSurname);
    notify(surnameChanged);
}

void Person::address(std::string newAddress)
{
    address_ = std::move(newAddress);
    notify(addressChanged);
}