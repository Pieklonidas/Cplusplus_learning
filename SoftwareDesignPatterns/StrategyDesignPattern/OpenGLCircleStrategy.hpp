#pragma once

#include "Circle.hpp"
#include "DrawStrategy.hpp"

class OpenGLCircleStrategy : public DrawStrategy<Circle>
{
public:
    void draw(const Circle& circle) const override;
};

