#include <iostream>
#include <vector>
#include "Spreadsheet.hpp"

Spreadsheet createObject()
{
    return Spreadsheet(3,2);
}

int main()
{
    std::vector<Spreadsheet> vec;
    for(int i = 0; i < 2; i++)
    {
        std::cout << "Iteration" << i << std::endl;
        vec.push_back(Spreadsheet(100, 100));
        std::cout << std::endl;
    }

    Spreadsheet s(2,3);
    std::cout << std::endl;
    s = createObject();
    std::cout << std::endl;
    Spreadsheet s2(5,6);
    std::cout << std::endl;
    s2 = s;
    std::cout << std::endl;
    return 0;
}