#pragma once

#include "IParagraph.hpp"
#include <string_view>

class Paragraph : public IParagraph
{
public:
    Paragraph(std::string_view text) : mText(text) {}
    virtual std::string getHTML() const override { return mText; }
private:
    std::string mText;
};