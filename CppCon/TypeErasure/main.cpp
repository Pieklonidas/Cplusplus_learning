#include <iostream>
#include <vector>
#include "Shape.hpp"

void drawAllShapes(const std::vector<Shape>& shapes)
{
    for(const auto& shape : shapes)
    {
        draw(shape);
    }
}

void serializeAllShapes(const std::vector<Shape>& shapes)
{
    for(const auto& shape : shapes)
    {
        serialize(shape);
    }
}

int main()
{
    using Shapes = std::vector<Shape>;

    Shapes shapes;
    shapes.emplace_back(Circle(2.2));
    shapes.emplace_back(Square(3.2));
    shapes.emplace_back(Circle(5.3));

    drawAllShapes(shapes);
    serializeAllShapes(shapes);
    return 0;
}