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

SpreadsheetCell SpreadsheetCell::operator+(const SpreadsheetCell& cell) const
{
    return SpreadsheetCell(getValue() + cell.getValue());
}

void SpreadsheetCell::setValue(double inValue)
{
    mValue = inValue;
}

inline double SpreadsheetCell::getValue() const
{
    numAccesses++;
    return mValue;
}

void SpreadsheetCell::setString(std::string_view inString)
{
    mValue = stringToDouble(inString);
}

inline std::string SpreadsheetCell::getString() const
{
    numAccesses++;
    return doubleToString(mValue);
}

void SpreadsheetCell::setColor(Color color) { mColor = color; }

SpreadsheetCell::Color SpreadsheetCell::getColor() { return mColor; }

std::string SpreadsheetCell::doubleToString(double inValue)
{
    return std::to_string(inValue);
}

double SpreadsheetCell::stringToDouble(std::string_view inString)
{
    return std::strtod(inString.data(), nullptr);
}