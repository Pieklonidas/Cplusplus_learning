#pragma once

#include "Square.hpp"
#include "Circle.hpp"
#include <iostream>

class Draw
{
public:
    void operator()(const Circle& circle) const
    {
        std::cout << "Drawing circle with radius: " << circle.getRadius() << std::endl;
    }

    void operator()(const Square& square) const
    {
        std::cout << "Drawing square with side: " << square.getSide() << std::endl;
    }
};