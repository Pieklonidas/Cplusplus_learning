#include "ElectricCar.hpp"
#include "ElectricEngine.hpp"

ElectricCar::ElectricCar()
    : Car(std::make_unique<ElectricEngine>())
{}

void ElectricCar::drive()
{
    getEngine()->start();
    getEngine()->stop();
}