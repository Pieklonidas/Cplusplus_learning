#pragma once

#include "Car.hpp"

class ElectricCar : public Car
{
public:
    explicit ElectricCar();
    void drive() override;
};