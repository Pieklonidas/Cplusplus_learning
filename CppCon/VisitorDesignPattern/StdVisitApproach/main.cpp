#include <iostream>
#include <vector>
#include <memory>
#include <variant>
#include "Square.hpp"
#include "Circle.hpp"
#include "Draw.hpp"

using Shape = std::variant<Circle, Square>;

void drawAllShapes(const std::vector<Shape>& shapes)
{
    for(const auto& s : shapes)
    {
        std::visit(Draw{}, s);
    }
}

int main()
{
    using Shapes = std::vector<Shape>;

    Shapes shapes;
    shapes.emplace_back( Circle(2.0) );
    shapes.emplace_back( Square(1.5) );
    shapes.emplace_back( Circle(2.5) );

    drawAllShapes(shapes);

    return 0;
}