#pragma once

#include "Observer.hpp"
#include <set>
#include <string>

class Person
{
public:
    enum StateChange
    {
        forenameChanged,
        surnameChanged,
        addressChanged
    };

    using PersonObserver = Observer<Person, StateChange>;
    explicit Person(std::string forename, std::string surname)
        : forename_(std::move(forename))
        , surname_(std::move(surname))
    {}

    bool attach(PersonObserver* observer);
    bool dettach(PersonObserver* observer);

    void notify(StateChange property);

    void forename(std::string newForename);
    void surname(std::string newSurname);
    void address(std::string newAddress);

    const std::string& forename() const { return forename_; }
    const std::string& surname () const { return surname_; }
    const std::string& address () const { return address_; }
    
    

private:
    std::string forename_;
    std::string surname_;
    std::string address_;

    std::set<PersonObserver*> observers_;
};