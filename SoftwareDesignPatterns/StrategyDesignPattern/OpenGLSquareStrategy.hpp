#pragma once

#include "Square.hpp"
#include "DrawStrategy.hpp"

class OpenGLSquareStrategy : public DrawStrategy<Square>
{
public:
    void draw(const Square& square) const override;
};

