#pragma once

template<unsigned char f>
class Factorial
{
public:
    static const unsigned long long val = (f * Factorial<f-1>::val);
};

template<>
class Factorial<0>
{
public:
    static const unsigned long long val = 1;
};

