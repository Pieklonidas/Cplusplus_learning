#pragma once
#include <optional>
#include "SpreadsheetCell.hpp"
#include "DoubleSpreadsheetCell.hpp"

class StringSpreadsheetCell : public SpreadsheetCell
{
public:
    StringSpreadsheetCell() = default;
    StringSpreadsheetCell(const DoubleSpreadsheetCell& inDoubleCell);
    virtual void set(std::string_view inString) override;
    virtual std::string getString() const override;

private:
    std::optional<std::string> mValue;
};

