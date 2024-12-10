#pragma once

#include "FileError.hpp"
#include <sstream>

class FileReadError : public FileError
{
public:
    FileReadError(std::string_view fileName, size_t lineNumber)
        : FileError(fileName), mLineNumber(lineNumber)
    {
        std::ostringstream ostr;
        ostr << "Error reading " << fileName << " at line " << lineNumber;
        setMessage(ostr.str());
    }

    size_t getLineNumber() const noexcept { return mLineNumber; }
private:
    size_t mLineNumber;
};
