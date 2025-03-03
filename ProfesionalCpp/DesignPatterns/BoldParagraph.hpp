#pragma once

#include "IParagraph.hpp"

class BoldParagraph : public IParagraph
{
public:
    BoldParagraph(const IParagraph& paragraph) : mWrapped(paragraph) {}
    virtual std::string getHTML() const override
    {
        return "<B>" + mWrapped.getHTML() + "</B>";
    }
private:
    const IParagraph& mWrapped;
};
