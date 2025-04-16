#pragma once

#include "Money.hpp"
#include <string>
#include <utility>

class ConferenceTicket
{
public:
    ConferenceTicket(std::string name, Money price)
        : name_(name), price_(price)
    {}

    const std::string& name() const { return name_; }
    Money price() const { return price_; }
private:
    std::string name_{};
    Money price_{0.0};
};