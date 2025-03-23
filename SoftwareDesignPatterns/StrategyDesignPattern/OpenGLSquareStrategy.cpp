#include "OpenGLSquareStrategy.hpp"
#include <iostream>

void OpenGLSquareStrategy::draw(const Square& square) const
{
    std::cout << "Drawing OpenGL square with side: " << square.side() << std::endl;
}