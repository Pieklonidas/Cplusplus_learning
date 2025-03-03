#pragma once

#include "IParagraph.hpp"

class ItalicParagraph : public IParagraph
{
public:
    ItalicParagraph(const IParagraph& paragraph) : mWrapped(paragraph) {}
    virtual std::string getHTML() const override
    {
        return "<I>" + mWrapped.getHTML() + "</I>";
    }
private:
    const IParagraph& mWrapped;
};
