#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
    SpreadsheetCell() = default;
    SpreadsheetCell(const SpreadsheetCell&) = default;
    SpreadsheetCell(double initialValue);
    SpreadsheetCell(std::string_view initialValue);

    SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

    void setValue(double inValue);
    double getValue() const;

    void setString(std::string_view inString);
    std::string getString() const;
private:
    std::string doubleToString(double inValue) const;
    double stringToDouble(std::string_view inString) const;
    double mValue;
};
