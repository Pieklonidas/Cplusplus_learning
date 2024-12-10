#include <iostream>
#include "SpreadsheetCell.hpp"

int main()
{
    SpreadsheetCell aThirdCell("test");
    std::cout << aThirdCell.getValue() << '\n';
    return 0;
}