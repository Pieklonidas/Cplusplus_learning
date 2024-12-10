#include <stdexcept>
#include <utility>
#include <iostream>
#include <algorithm>
#include "Spreadsheet.hpp"

// size_t Spreadsheet::sCounter;

Spreadsheet::Spreadsheet(size_t width, size_t height)
    : mId(sCounter++)
    , mWidth(std::min(width, kMaxWidth))
    , mHeight(std::min(height, kMaxHeight))
{
    std::cout << "Parametrized constructor" << std::endl;
    mCells = new SpreadsheetCell*[mWidth];
    for(size_t i = 0; i < mWidth; i++)
    {
        mCells[i] = new SpreadsheetCell[mHeight];
    }
}

Spreadsheet::Spreadsheet(const Spreadsheet& src)
    : Spreadsheet(src.mWidth, src.mHeight)
{
    std::cout << "Copy constructor" << std::endl;
    for(size_t i = 0; i < mWidth; i++)
    {
        for(size_t j = 0; j < mHeight; j++)
        {
            mCells[i][j] = src.mCells[i][j];
        }
    }
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
    std::cout << "Copy assignment operator" << std::endl;
    if(this == &rhs) return *this;
    Spreadsheet temp(rhs);
    swap(*this, temp);
    return *this;
}

Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
    : Spreadsheet()
{
    std::cout << "Move constructor" << std::endl;
    swap(*this, src);
}

Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
{
    std::cout << "move assignment operator" << std::endl;
    Spreadsheet temp(std::move(rhs));
    swap(*this, temp);
    return *this;
}

Spreadsheet::~Spreadsheet()
{
    for(size_t i = 0; i < mWidth; i++)
    {
        delete[] mCells[i];
    }
    delete[] mCells;
    mCells = nullptr;
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
    verifyCoordinates(x, y);
    mCells[x][y] = cell;
}

const SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) const
{
    verifyCoordinates(x, y);
    return mCells[x][y];
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
    return const_cast<SpreadsheetCell&>(std::as_const(*this).getCellAt(x,y));
}

size_t Spreadsheet::getId() const
{
    return mId;
}

void Spreadsheet::verifyCoordinates(size_t x, size_t y) const
{
    if (x >= mWidth || y >= mHeight) throw std::out_of_range("");
}

void Spreadsheet::cleanup() noexcept
{
    for(size_t i = 0; i < mWidth; i++)
    {
        delete[] mCells[i];
    }
    delete[] mCells;
    mCells = nullptr;
    mWidth = mHeight = 0;
}

void Spreadsheet::moveFrom(Spreadsheet& src) noexcept
{
    mWidth = src.mWidth;
    mHeight = src.mHeight;
    mCells = src.mCells;

    src.mWidth = 0;
    src.mHeight = 0;
    src.mCells = nullptr;
}

void swap(Spreadsheet& first, Spreadsheet& second) noexcept
{
    using std::swap;

    swap(first.mWidth, second.mWidth);
    swap(first.mHeight, second.mHeight);
    swap(first.mCells, second.mCells);
}