#include <iostream>
#include <memory>
#include <vector>
#include "StringSpreadsheetCell.hpp"
#include "DoubleSpreadsheetCell.hpp"

StringSpreadsheetCell operator+(const StringSpreadsheetCell& lhs, const StringSpreadsheetCell& rhs)
{
    StringSpreadsheetCell newCell;
    newCell.set(lhs.getString() + rhs.getString());
    return newCell;
}

int main()
{
    std::vector<std::unique_ptr<SpreadsheetCell>> cellArray;
    cellArray.push_back(std::make_unique<StringSpreadsheetCell>());
    cellArray.push_back(std::make_unique<StringSpreadsheetCell>());
    cellArray.push_back(std::make_unique<DoubleSpreadsheetCell>());
    cellArray[0]->set("hello");
    cellArray[1]->set("10");
    cellArray[2]->set("18");
    std::cout << "Vector values are [" << cellArray[0]->getString() << ", " <<
                                          cellArray[1]->getString() << ", " <<
                                          cellArray[2]->getString() << "]" <<
                                          std::endl;
    
    DoubleSpreadsheetCell myDbl;
    myDbl.set(8.4);
    StringSpreadsheetCell result = myDbl + myDbl;

    std::cout << "Concatenated string: " << result.getString() << std::endl;

    return 0;
}