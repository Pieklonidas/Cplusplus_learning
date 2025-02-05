#pragma once
#include <iostream>

template <typename T>
class PointerClass
{
public:
    PointerClass(T x_) : x(x_) {}
    const T getX() const { std::cout << "Normal" << std::endl; return x; }
    void setX(T val) { x = val; }
private:
    T x;
};

template <typename T>
class PointerClass<T*>
{
public:
    PointerClass(T* x_) : x(x_) {}
    const T* getX() const { std::cout << "Specialized" << std::endl; return x; } ;
    void setX(T val) { *x = val; }
private:
    T* x;
};