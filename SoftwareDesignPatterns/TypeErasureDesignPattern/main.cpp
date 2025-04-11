#include "Circle.hpp"
#include "Square.hpp"
#include "Shape.hpp"
#include <iostream>
#include <cstdlib>

int main()
{
    Circle circle{3.14};

    auto drawer = [](Circle const& c)
        { std::cout << "Drawing circle with radius: " << c.radius() << std::endl; };

    Shape shape1(circle, drawer);

    draw(shape1);

    Shape shape2(shape1);

    draw(shape2);

    return 0;
}