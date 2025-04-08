#include "Sheep.hpp"
#include <iostream>

void Sheep::makeSound() const
{
    std::cout << name_ << ": baa\n";
}

std::unique_ptr<Animal> Sheep::clone() const
{
    return std::make_unique<Sheep>(*this);
}