#pragma once

class Circle;
class Square;

class ShapeVisitor
{
public:
    virtual ~ShapeVisitor() = default;
    virtual void visit(const Circle&) const = 0;
    virtual void visit(const Square&) const = 0;
};