#pragma once

#include <exception>
#include <string>
#include <string_view>

class MyException : public std::exception
{
public:
    MyException(std::string_view message) : mMessage(message) {}
    virtual const char* what() const noexcept override
    {
        return mMessage.c_str();
    }
private:
    std::string mMessage;
};

