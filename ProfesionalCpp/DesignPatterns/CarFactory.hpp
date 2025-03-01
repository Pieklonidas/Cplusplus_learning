#pragma once
#include "Car.hpp"
#include <cstddef>
#include <memory>

class CarFactory
{
public:
    virtual ~CarFactory() = default;
    std::unique_ptr<Car> requestCar();
    size_t getNumberOfCarsProduced() const;
protected:
    virtual std::unique_ptr<Car> createCar() = 0;
private:
    size_t mNumberOfCarsProduced = 0;
};

class FordFactory final : public CarFactory
{
protected:
    virtual std::unique_ptr<Car> createCar() override;
};

class ToyotaFactory final : public CarFactory
{
protected:
    virtual std::unique_ptr<Car> createCar() override;
};