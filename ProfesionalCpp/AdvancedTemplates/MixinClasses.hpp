#pragma once
#include <iostream>

class Mixin1
{
public:
    Mixin1(int i) : mValue(i) {}
    virtual void Mixin1Func() { std::cout << "Mixin1: " << mValue << std::endl; }
private:
    int mValue;
};

class Mixin2
{
public:
    Mixin2(int i) : mValue(i) {}
    virtual void Mixin2Func() { std::cout << "Mixin1: " << mValue << std::endl; }
private:
    int mValue;
};

template <typename... Mixins>
class MyClass : public Mixins...
{
public:
    MyClass(const Mixins&... mixins) : Mixins(mixins)... {}
    virtual ~MyClass() = default;
};