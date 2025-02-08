#pragma once
#include <iostream>
#include <tuple>

template<typename TupleType, int n>
class tuple_print
{
public:
    tuple_print(const TupleType& t)
    {
        tuple_print<TupleType, n-1> tp(t);
        std::cout << get<n-1>(t) << std::endl;
    }
};

template <typename TupleType>
class tuple_print<TupleType, 0>
{
public:
    tuple_print(const TupleType&) { }
};

template<typename TupleType, int n = std::tuple_size<TupleType>::value>
void tuple_print2(const TupleType& t)
{
    if constexpr(n > 1)
    {
        tuple_print2<TupleType, n-1>(t);
    }
    std::cout << get<n-1>(t) << std::endl;
}