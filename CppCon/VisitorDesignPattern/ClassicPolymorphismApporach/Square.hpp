#pragma once

#include "Shape.hpp"

class Square : public Shape
{
public:
    explicit Square(double s)
        : side(s) {}
    
    double getSide() const noexcept { return side; }

    void accept(const ShapeVisitor& shapeVisitor) override
    {
        shapeVisitor.visit(*this);
    }
private:
    double side;
};