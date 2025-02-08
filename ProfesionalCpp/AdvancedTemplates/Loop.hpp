#pragma once

template <int i>
class Loop
{
public:
    template <typename FuncType>
    static inline void Do(FuncType func)
    {
        Loop<i-1>::Do(func);
        func(i);
    }
};

template<>
class Loop<0>
{
public:
    template <typename FuncType>
    static inline void Do(FuncType) {}
};