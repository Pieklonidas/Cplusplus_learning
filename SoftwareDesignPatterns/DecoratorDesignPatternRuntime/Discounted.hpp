#pragma once

#include "Item.hpp"
#include <cmath>

class Discounted
{
public:
    Discounted(double discount, Item item)
        : item_( std::move(item) ), factor_( 1.0 - discount )
    {}

    Money price() const
    {
        return item_.price()*factor_;
    }

private:
    Item item_;
    double factor_;
};