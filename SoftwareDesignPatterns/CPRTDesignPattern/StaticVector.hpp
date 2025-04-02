#pragma once

#include "DenseVector.hpp"
#include <iostream>
#include <array>

template <typename T, size_t Size>
class StaticVector : public DenseVector<StaticVector<T, Size>>
{
public:
    size_t size() const
    {
        std::cout << "Returning size of array" << std::endl;
        return arr_.size();
    }
private:
    std::array<T, Size> arr_;
};