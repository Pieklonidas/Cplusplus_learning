#pragma once
#include <iostream>

class Counter
{
public:
    Counter(int id, int numIterations) 
        : mId(id), mNumIterations(numIterations) 
    {
    }

    void operator()() const
    {
        for(int i = 0; i < mNumIterations; ++i)
        {
            std::cout << "Counter " << mId << " has value " << i << std::endl;
        }
    }
private:
    int mId;
    int mNumIterations;
};

