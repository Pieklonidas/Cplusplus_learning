#pragma once

#include "Item.hpp"
#include <string>
#include <utility>

class ConferenceTicket : public Item
{
public:
    ConferenceTicket(std::string name, Money price)
        : name_(name), price_(price)
    {}

    const std::string& name() const { return name_; }
    Money price() const override { return price_; }
private:
    std::string name_{};
    Money price_{0.0};
};