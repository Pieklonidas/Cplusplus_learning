#include <iostream>
#include "DynamicVector.hpp"
#include "StaticVector.hpp"

template <typename T>
void sizeOfVector(const DenseVector<T>& vector)
{
    std::cout << vector.size() << std::endl;
}

int main()
{
    DynamicVector<int> dynVec;
    StaticVector<int, 5> statVec;

    sizeOfVector(dynVec);
    sizeOfVector(statVec);

    return 0;
}