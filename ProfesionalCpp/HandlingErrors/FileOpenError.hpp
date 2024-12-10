#pragma once

#include "FileError.hpp"

class FileOpenError : public FileError
{
public:
    FileOpenError(std::string_view fileName) : FileError(fileName)
    {
        setMessage("Unable to open "s + fileName.data());
    }
};
