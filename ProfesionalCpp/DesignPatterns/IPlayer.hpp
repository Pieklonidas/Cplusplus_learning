#pragma once
#include <string>
#include <string_view>

class IPlayer
{
public:
    virtual std::string getName() const = 0;
    virtual std::string sendInstantMessage(std::string_view message) const = 0;
};