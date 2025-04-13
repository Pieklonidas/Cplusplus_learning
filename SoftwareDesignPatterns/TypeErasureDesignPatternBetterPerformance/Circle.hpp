#pragma once

class Circle
{
public:
    explicit Circle(double radius)
        : radius_(radius)
    {}
    double radius() const { return radius_; }
private:
    double radius_;
};