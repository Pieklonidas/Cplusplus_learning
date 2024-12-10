#include "SpreadsheetCell.hpp"

SpreadsheetCell::SpreadsheetCell(double initialValue) : mValue(initialValue) {}
SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
{
    setString(initialValue);
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
    if(this == &rhs) return *this;
    this->mValue = rhs.mValue;
    return *this;
}

void SpreadsheetCell::setValue(double inValue)
{
    mValue = inValue;
}

double SpreadsheetCell::getValue() const
{
    return mValue;
}

void SpreadsheetCell::setString(std::string_view inString)
{
    mValue = stringToDouble(inString);
}

std::string SpreadsheetCell::getString() const
{
    return doubleToString(mValue);
}

std::string SpreadsheetCell::doubleToString(double inValue) const
{
    return std::to_string(inValue);
}

double SpreadsheetCell::stringToDouble(std::string_view inString) const
{
    return std::strtod(inString.data(), nullptr);
}