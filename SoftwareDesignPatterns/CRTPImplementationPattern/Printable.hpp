#pragma once

#include <iostream>

template<typename Derived>
struct Printable
{
    friend std::ostream& operator<<(std::ostream& os, const Derived& d)
    {
        os << d.get();
        return os;
    }
};
