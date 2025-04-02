#pragma once

#include "DenseVector.hpp"
#include <iostream>
#include <vector>

template <typename T>
class DynamicVector : public DenseVector<DynamicVector<T>>
{
public:
    size_t size() const
    {
        std::cout << "Returning size of vector" << std::endl;
        return vec_.size();
    }
private:
    std::vector<T> vec_;
};