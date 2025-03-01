#pragma once
#include <string_view>

class Car
{
public:
    virtual ~Car() = default;
    virtual std::string_view info() const = 0;
};

class Ford final : public Car
{
public:
    virtual std::string_view info() const { return "Ford"; }
};

class Toyota final : public Car
{
public:
    virtual std::string_view info() const { return "Toyota"; }
};