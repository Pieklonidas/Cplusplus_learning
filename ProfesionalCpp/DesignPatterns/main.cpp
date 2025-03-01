#include <iostream>
#include "Logger.hpp"
#include "LeastBusyFactory.hpp"

void singletonExample()
{
    Logger::instance().setLogLevel(Logger::LogLevel::Debug);

    Logger::instance().log("test message", Logger::LogLevel::Debug);
    std::vector<std::string> items = {"item1", "item2"};
    Logger::instance().log(items, Logger::LogLevel::Error);
    Logger::instance().setLogLevel(Logger::LogLevel::Error);
    Logger::instance().log("A debug message", Logger::LogLevel::Debug);
}

void factoryExample()
{
    ToyotaFactory myFactory;
    auto myCar = myFactory.requestCar();
    std::cout << myCar->info() << std::endl;

    std::vector<std::unique_ptr<CarFactory>> factories;

    factories.push_back(std::make_unique<FordFactory>());
    factories.push_back(std::make_unique<FordFactory>());
    factories.push_back(std::make_unique<FordFactory>());
    factories.push_back(std::make_unique<ToyotaFactory>());

    factories[0]->requestCar();
    factories[0]->requestCar();
    factories[1]->requestCar();
    factories[3]->requestCar();

    LeastBusyFactory LeastBusyFactory(std::move(factories));
    for(size_t i = 0; i < 10; ++i)
    {
        auto theCar = LeastBusyFactory.requestCar();
        std::cout << theCar->info() << std::endl;
    }
}

int main()
{
    // singletonExample();
    factoryExample();
    return 0;
}