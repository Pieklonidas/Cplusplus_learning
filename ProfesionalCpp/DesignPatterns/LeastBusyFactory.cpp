#include "LeastBusyFactory.hpp"
#include <stdexcept>

LeastBusyFactory::LeastBusyFactory(std::vector<std::unique_ptr<CarFactory>>&& factories)
    : mFactories(std::move(factories))
{
    if(mFactories.empty())
    {
        throw std::runtime_error("No factories provided.");
    }
}

std::unique_ptr<Car> LeastBusyFactory::createCar()
{
    CarFactory* bestSoFar = mFactories[0].get();
    for(auto& factory : mFactories)
    {
        if(factory->getNumberOfCarsProduced() < bestSoFar->getNumberOfCarsProduced())
        {
            bestSoFar = factory.get();
        }
    }
    return bestSoFar->requestCar();
}