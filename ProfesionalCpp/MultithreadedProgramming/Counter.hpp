#pragma once
#include <iostream>
#include <mutex>

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
            std::lock_guard lock(sMutex);
            std::cout << "Counter " << mId << " has value " << i << std::endl;
        }
    }
private:
    int mId;
    int mNumIterations;
    static std::mutex sMutex;
};

std::mutex Counter::sMutex;
