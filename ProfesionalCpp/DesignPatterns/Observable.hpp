#pragma once
#include "IObserver.hpp"
#include <algorithm>
#include <vector>

class Observable
{
public:
    virtual ~Observable() = default;

    void addObserver(IObserver* observer)
    {
        mObservers.push_back(observer);
    }

    void removeObserver(IObserver* observer)
    {
        mObservers.erase(
            std::remove(begin(mObservers), end(mObservers), observer),
            end(mObservers));
    }

protected:
    void notifyAllObservers()
    {
        for(auto* observer : mObservers)
        {
            observer->notify();
        }
    }

private:
    std::vector<IObserver*> mObservers;
};