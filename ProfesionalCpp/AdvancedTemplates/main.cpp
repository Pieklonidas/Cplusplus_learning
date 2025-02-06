#include <iostream>
#include <vector>
#include <deque>
#include <string_view>
#include <string>
#include "PartialSpecializationPointerClass.hpp"
#include "MixinClasses.hpp"

template<typename T,
    template <typename E, typename Allocator = std::allocator<E>> class Container = std::vector>
Container<T> makeAContainer(T a, T b, T step)
{
    Container<T> temp;
    for(T start = a; start <= b; start+=step)
    {
        temp.push_back(start);
    }
    return temp;
}

void templateTemplateParamterExample()
{
    auto container = makeAContainer<int, std::vector>(0, 10, 2);
    for(const auto elem : container)
    {
        std::cout << elem << std::endl;
    }

    auto container2 = makeAContainer<int, std::deque>(10, 16, 2);
    for(const auto elem : container2)
    {
        std::cout << elem << std::endl;
    }
}

class ObjectA
{
public:
    int x = 1;
    int y = 2;
};

template <typename T, const T DEFAULT>
void coutAddedValue(T val)
{
    std::cout << val + DEFAULT << std::endl;
}

template <typename T, const T& DEFAULT>
void coutObject(T val)
{
    std::cout << val.x + DEFAULT.x << " " << val.y + DEFAULT.x << std::endl;
}

namespace 
{
    ObjectA A{5, 7};
}

void nonTypeParamterExample()
{
    coutAddedValue<int, 7>(7);
    coutAddedValue<char, char(5)>('a');
    ObjectA B{5, 7};
    coutObject<ObjectA, A>(B);
}

void partialSpecializationExample()
{
    int x = 1;
    PointerClass A(x);
    std::cout << A.getX() << std::endl;
    {
        PointerClass B(&x);
        std::cout << B.getX() << std::endl;
        std::cout << *B.getX() << std::endl;
        A.setX(5);
        std::cout << A.getX() << std::endl;
        std::cout << *B.getX() << std::endl;
        std::cout << "Just x: " << x << std::endl;
        B.setX(10);
        std::cout << A.getX() << std::endl;
        std::cout << *B.getX() << std::endl;
        std::cout << "Just x: " << x << std::endl;
    }
    std::cout << "Still x: " << x << std::endl;
}

void handleValue(int value) { std::cout << "Integer: " << value << std::endl; }
void handleValue(double value) { std::cout << "Double: " << value << std::endl; }
void handleValue(std::string_view value) { std::cout << "String: " << value << std::endl; }

void processValues() {};

template <typename T1, typename... Tn>
void processValues(T1&& arg1, Tn&&... args)
{
    handleValue(std::forward<T1>(arg1));
    processValues(std::forward<Tn>(args)...);
}

void variadicTemplateFunctionExample()
{
    processValues(1, 2, 3.56, "test", 1.1f);
}

void mixinClassesExample()
{
    MyClass<Mixin1, Mixin2> a(Mixin1(11), Mixin2(22));
    a.Mixin1Func();
    a.Mixin2Func();

    MyClass<Mixin1> b(Mixin1(33));
    b.Mixin1Func();

    MyClass<> c;
}

template <typename... Tn>
void processValues2(const Tn&... args)
{
    (handleValue(args), ...);
}

template <typename... Values>
void printValues(const Values&... values)
{
    ((std::cout << values << std::endl), ...);
}

template <typename T, typename... Values>
double sumValues(const T& init, const Values&... values)
{
    return (init + ... + values);
}

void foldingExpressionsExample()
{
    processValues2(1, "test", 2.34);
    printValues(1, "test", 2.34);
    std::cout << sumValues(4.34) << std::endl;
    std::cout << sumValues(2.34, 2.12, 5.34, 10.17) << std::endl;
}

int main()
{
    // templateTemplateParamterExample();
    // nonTypeParamterExample();
    // partialSpecializationExample();
    // variadicTemplateFunctionExample();
    // mixinClassesExample();
    foldingExpressionsExample();
    return 0;
}