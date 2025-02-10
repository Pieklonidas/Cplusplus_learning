#pragma once
#include <iostream>

class Request
{
public:
    Request(int id) : mId(id) {}

    void process()
    {
        std::cout << "Processing request " << mId << std::endl;
    }
private:
    int mId;
};