#pragma once

#include <exception>
#include <string>
#include <string_view>

using namespace std::string_literals;

class FileError : public std::exception
{
public:
    FileError(std::string_view fileName) : mFileName(fileName) {}
    
    virtual const char* what() const noexcept override
    {
        return mMessage.c_str();
    }

    std::string_view getFileName() const noexcept { return mFileName; }

protected:
    void setMessage(std::string_view message) { mMessage = message; }
private:
    std::string mFileName;
    std::string mMessage;
};

