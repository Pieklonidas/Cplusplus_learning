#pragma once

#include "Item.hpp"
#include <string>
#include <utility>

class CppBook : public Item
{
public:
    CppBook(std::string title, Money price)
        : title_(title), price_(price)
    {}

    const std::string& title() const { return title_; }
    Money price() const override { return price_; }
private:
    std::string title_{};
    Money price_{0.0};
};