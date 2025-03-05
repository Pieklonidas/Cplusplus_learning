#pragma once

#include "Square.hpp"
#include "Circle.hpp"
#include <iostream>

class Draw : public ShapeVisitor
{
public:
    void visit(const Circle& circle) const override
    {
        std::cout << "Drawing circle with radius: " << circle.getRadius() << std::endl;
    }

    void visit(const Square& square) const override
    {
        std::cout << "Drawing square with side: " << square.getSide() << std::endl;
    }
};