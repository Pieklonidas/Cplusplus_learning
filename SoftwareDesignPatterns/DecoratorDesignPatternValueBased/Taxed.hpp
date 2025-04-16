#pragma once

#include "PricedItem.hpp"
#include <utility>
#include <cmath>

template <double taxRate, PricedItem Item>
class Taxed : private Item
{
public:
    template <typename... Args>
    explicit Taxed(Args&&... args)
        : Item{ std::forward<Args>(args)... }
    {}

    Money price() const
    {
        return Item::price()*(1.0 + taxRate);
    }
};