#include "OpenGLCircleStrategy.hpp"
#include <iostream>

void OpenGLCircleStrategy::draw(const Circle& circle) const
{
    std::cout << "Drawing OpenGL circle with radius: " << circle.radius() << std::endl;
}