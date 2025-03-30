#pragma once
#include <iostream>

class OpenPages
{
public:
    void convertToBytes() const
    {
        std::cout << "converting OpenPages to bytes" << std::endl;
    }
};

void exportToJSONFormat(const OpenPages&)
{
    std::cout << "exporting OpenPages to JSON format" << std::endl;
}