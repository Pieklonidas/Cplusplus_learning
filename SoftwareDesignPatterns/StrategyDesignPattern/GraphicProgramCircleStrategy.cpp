#include "GraphicProgramCircleStrategy.hpp"
#include <iostream>

void GraphicProgramCircleStrategy::draw(const Circle& circle) const
{
    std::cout << "Drawing GraphicProgram circle with radius: " << circle.radius() << std::endl;
}