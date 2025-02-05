#include <iostream>
#include <vector>
#include <deque>
#include "PartialSpecializationPointerClass.hpp"

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

int main()
{
    // templateTemplateParamterExample();
    // nonTypeParamterExample();
    partialSpecializationExample();
    return 0;
}