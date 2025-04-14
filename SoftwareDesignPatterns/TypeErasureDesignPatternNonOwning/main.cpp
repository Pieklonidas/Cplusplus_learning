#include "Circle.hpp"
#include "Square.hpp"
#include "Shape.hpp"
#include <iostream>
#include <cstdlib>

void useShapeConstRef(ShapeConstRef shape)
{
    draw(shape);
}

int main()
{
    Circle circle{ 3.14 };
    auto drawer = [](const Circle& c)
    { 
        std::cout << "Drawing circle with radius: " << c.radius() << std::endl;
    };

    useShapeConstRef({ circle, drawer });

    return 0;
}