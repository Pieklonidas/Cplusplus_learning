#include <cstddef>
#include "SpreadsheetCell.hpp"

class Spreadsheet
{
public:
    Spreadsheet(size_t width, size_t height);
    Spreadsheet(const Spreadsheet& src);
    Spreadsheet& operator=(const Spreadsheet& rhs);
    Spreadsheet(Spreadsheet&& src) noexcept;
    Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;

    ~Spreadsheet();

    void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
    const SpreadsheetCell& getCellAt(size_t x, size_t y) const;
    SpreadsheetCell& getCellAt(size_t x, size_t y);
    size_t getId() const;

    static const size_t kMaxHeight = 100;
    static const size_t kMaxWidth = 100;

    friend void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
private:
    Spreadsheet() = default;

    void verifyCoordinates(size_t x, size_t y) const;
    void cleanup() noexcept;
    void moveFrom(Spreadsheet& src) noexcept;
    
    static inline size_t sCounter = 0;

    size_t mId = 0;
    size_t mWidth = 0;
    size_t mHeight = 0;
    SpreadsheetCell** mCells = nullptr;

};
