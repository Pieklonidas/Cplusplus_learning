#pragma once

#include "Money.hpp"
#include <concepts>

template <typename T>
concept PricedItem =
    requires (T item)
    {
        {item.price()} -> std::same_as<Money>;
    };