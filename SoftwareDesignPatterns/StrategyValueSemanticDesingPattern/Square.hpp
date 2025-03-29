#pragma once

#include "Shape.hpp"
#include "Point.hpp"
#include <functional>
#include <utility>

class Square : public Shape
{

public:
    using DrawStrategy = std::function<void(const Square&)>;
    Square(double side, DrawStrategy drawer)
        : side_(side), drawer_(std::move(drawer)) {}

    double side() const { return side_; }
    Point center() const { return center_; }

    void draw() const override;
private:
    double side_;
    Point center_{};
    DrawStrategy drawer_;
};