#pragma once

#include "Shape.hpp"
#include "Point.hpp"
#include "DrawStrategy.hpp"
#include <memory>
#include <utility>

class Square : public Shape
{

public:
    Square(double side, std::unique_ptr<DrawStrategy<Square>> drawer)
        : side_(side), drawer_(std::move(drawer)) {}

    double side() const { return side_; }
    Point center() const { return center_; }

    void draw() const override;
private:
    double side_;
    Point center_{};
    std::unique_ptr<DrawStrategy<Square>> drawer_;
};