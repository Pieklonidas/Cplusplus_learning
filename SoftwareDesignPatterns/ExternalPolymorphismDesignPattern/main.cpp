#include "Circle.hpp"
#include "Square.hpp"
#include "Shape.hpp"
#include "OpenGLDrawingStrategy.hpp"
#include <memory>
#include <vector>

int main()
{
    using Shapes = std::vector<std::unique_ptr<ShapeConcept>>;

    using CircleModel = ShapeModel<Circle,OpenGLDrawingStrategy>;
    using SquareModel = ShapeModel<Square,OpenGLDrawingStrategy>;

    Shapes shapes{};

    shapes.emplace_back(
        std::make_unique<CircleModel>(
            Circle{2.3}, OpenGLDrawingStrategy() ) );
    shapes.emplace_back(
        std::make_unique<SquareModel>(
            Square{1.2}, OpenGLDrawingStrategy() ) );
    shapes.emplace_back(
        std::make_unique<CircleModel>(
            Circle{4.1}, OpenGLDrawingStrategy() ) );

    for( auto const& shape : shapes )
    {
        shape->draw();
    }
    return 0;
}