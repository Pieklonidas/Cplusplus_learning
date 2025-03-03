#pragma once
#include <string>

class IParagraph
{
public:
    virtual ~IParagraph() = default;
    virtual std::string getHTML() const = 0;
};