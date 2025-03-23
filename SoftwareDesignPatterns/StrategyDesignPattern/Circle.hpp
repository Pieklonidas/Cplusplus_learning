#pragma once

#include "Shape.hpp"
#include "Point.hpp"
#include "DrawStrategy.hpp"
#include <memory>
#include <utility>

class Circle : public Shape
{
public:
    explicit Circle(double radius, std::unique_ptr<DrawStrategy<Circle>> drawer)
        : radius_(radius), drawer_(std::move(drawer)) {}
    double radius() const { return radius_; }
    Point center() const { return center_; }

    void draw() const override;
private:
    double radius_;
    std::unique_ptr<DrawStrategy<Circle>> drawer_;
    Point center_{};
};

