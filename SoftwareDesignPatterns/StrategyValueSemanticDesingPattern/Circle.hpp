#pragma once

#include "Shape.hpp"
#include "Point.hpp"
#include <functional>
#include <utility>

class Circle : public Shape
{
public:
    using DrawStrategy = std::function<void(const Circle&)>;
    explicit Circle(double radius, DrawStrategy drawer)
        : radius_(radius), drawer_(std::move(drawer)) {}
    double radius() const { return radius_; }
    Point center() const { return center_; }

    void draw() const override;
private:
    double radius_;
    DrawStrategy drawer_;
    Point center_{};
};

