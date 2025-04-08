#pragma once

#include "Animal.hpp"
#include <string>

class Sheep : public Animal
{
public:
    Sheep(std::string name) : name_(std::move(name)) {}
    void makeSound() const override;
    std::unique_ptr<Animal> clone() const override;
private:
    std::string name_;
};