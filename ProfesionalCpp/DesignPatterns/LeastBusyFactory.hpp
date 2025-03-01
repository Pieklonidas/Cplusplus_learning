#pragma once
#include "CarFactory.hpp"
#include <vector>

class LeastBusyFactory final : public CarFactory
{
public:
    explicit LeastBusyFactory(std::vector<std::unique_ptr<CarFactory>>&& factories);
protected:
    virtual std::unique_ptr<Car> createCar() override;
private:
    std::vector<std::unique_ptr<CarFactory>> mFactories;
};