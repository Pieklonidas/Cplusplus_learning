#include "Sheep.hpp"

int main()
{
    std::unique_ptr<Animal> Dolly = std::make_unique<Sheep>("Dolly");
    std::unique_ptr<Animal> cloneDolly = Dolly->clone();
    Dolly->makeSound();
    cloneDolly->makeSound();
    return 0;
}