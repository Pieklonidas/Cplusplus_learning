#include "StringSpreadsheetCell.hpp"

StringSpreadsheetCell::StringSpreadsheetCell(const DoubleSpreadsheetCell& inDoubleCell)
{
    mValue = inDoubleCell.getString();
}

void StringSpreadsheetCell::set(std::string_view inString)
{
    mValue = inString;
}

std::string StringSpreadsheetCell::getString() const
{
    return mValue.value_or("");
}