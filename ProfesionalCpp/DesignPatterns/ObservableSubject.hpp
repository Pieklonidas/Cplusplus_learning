#pragma once
#include "Observable.hpp"

class ObservableSubject : public Observable
{
public:
    void modifyData()
    {
        std::cout << "Modifying data" << std::endl;
        notifyAllObservers();
    }
};