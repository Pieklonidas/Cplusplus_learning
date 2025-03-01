#include "CarFactory.hpp"

std::unique_ptr<Car> CarFactory::requestCar()
{
    ++mNumberOfCarsProduced;
    return createCar();
}

size_t CarFactory::getNumberOfCarsProduced() const
{
    return mNumberOfCarsProduced;
}

std::unique_ptr<Car> FordFactory::createCar()
{
    return std::make_unique<Ford>();
}

std::unique_ptr<Car> ToyotaFactory::createCar()
{
    return std::make_unique<Toyota>();
}