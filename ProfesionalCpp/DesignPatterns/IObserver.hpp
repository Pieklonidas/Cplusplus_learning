#pragma once
#include <iostream>

class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void notify() = 0;
};

class ConcreteObserver1 : public IObserver
{
public:
    void notify() override
    {
        std::cout << "ConcreteObserver1::notify()" << std::endl;
    }
};

class ConcreteObserver2 : public IObserver
{
public:
    void notify() override
    {
        std::cout << "ConcreteObserver2::notify()" << std::endl;
    }
};