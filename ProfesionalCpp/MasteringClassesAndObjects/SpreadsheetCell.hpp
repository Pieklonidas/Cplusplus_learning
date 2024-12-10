#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
    enum class Color { Red = 1, Green, Blue, Yellow };

    SpreadsheetCell() = default;
    SpreadsheetCell(const SpreadsheetCell&) = default;
    SpreadsheetCell(double initialValue);
    SpreadsheetCell(std::string_view initialValue);

    SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
    SpreadsheetCell operator+(const SpreadsheetCell& cell) const;
    void setValue(double inValue);
    double getValue() const;

    void setString(std::string_view inString);
    std::string getString() const;

    void setColor(Color color);
    Color getColor();
private:
    static std::string doubleToString(double inValue);
    static double stringToDouble(std::string_view inString);
    double mValue;
    mutable size_t numAccesses = 0;
    Color mColor = Color::Red;
};
