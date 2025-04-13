#include "Circle.hpp"
#include "Square.hpp"
#include <iostream>

class OpenGLDrawingStrategy
{
public:
    void operator()(const Circle& circle) const
    {
        std::cout << "Drawing circle with radius: " << circle.radius() << std::endl;
    }

    void operator()(const Square& square) const
    {
        std::cout << "Drawing square with side: " << square.side() << std::endl;
    }
};