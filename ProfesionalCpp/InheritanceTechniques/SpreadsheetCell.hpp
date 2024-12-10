#pragma once
#include <string_view>
#include <string>

class SpreadsheetCell
{
public:
    virtual ~SpreadsheetCell() = default;
    virtual void set(std::string_view inString) = 0;
    virtual std::string getString() const = 0;
};