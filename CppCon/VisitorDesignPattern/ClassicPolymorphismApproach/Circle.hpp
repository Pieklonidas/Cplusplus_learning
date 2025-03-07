#pragma once

#include "Shape.hpp"

class Circle : public Shape
{
public:
    explicit Circle(double rad)
        : radius(rad) {}
    
    double getRadius() const noexcept { return radius; }
    
    void accept(const ShapeVisitor& shapeVisitor) override
    {
        shapeVisitor.visit(*this);
    }
private:
    double radius;
};