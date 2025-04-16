#pragma once

#include "PricedItem.hpp"
#include <utility>
#include <cmath>

template <double discount, PricedItem Item>
class Discounted
{
public:
    template <typename... Args>
    explicit Discounted(Args&&... args)
        : item_{ std::forward<Args>(args)... }
    {}

    Money price() const
    {
        return item_.price()*(1.0 - discount);
    }

private:
    Item item_;
};