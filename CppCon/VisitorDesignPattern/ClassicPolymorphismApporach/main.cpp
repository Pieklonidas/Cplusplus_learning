#include <iostream>
#include "Draw.hpp"
#include <vector>
#include <memory>

void drawAllShapes(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    for(const auto& s : shapes)
    {
        s->accept( Draw{} );
    }
}

int main()
{
    using Shapes = std::vector<std::unique_ptr<Shape>>;\

    Shapes shapes;
    shapes.emplace_back( std::make_unique<Circle>(2.0) );
    shapes.emplace_back( std::make_unique<Square>(1.5) );
    shapes.emplace_back( std::make_unique<Circle>(2.5) );

    drawAllShapes(shapes);

    return 0;
}