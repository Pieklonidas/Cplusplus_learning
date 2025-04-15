#pragma once

#include "Money.hpp"

class Item
{
public:
    virtual ~Item() = default;
    virtual Money price() const = 0;
};