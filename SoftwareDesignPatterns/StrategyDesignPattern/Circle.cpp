#include "Circle.hpp"

void Circle::draw() const
{
    drawer_->draw(*this);
}