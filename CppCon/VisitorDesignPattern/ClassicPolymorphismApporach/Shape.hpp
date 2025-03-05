#pragma once

#include "ShapeVisitor.hpp"

class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual void accept(const ShapeVisitor&) = 0;
};

