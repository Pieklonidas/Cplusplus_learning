#pragma once
#include "Document.hpp"

class Word : public Document
{
public:
    virtual void exportToJSON() const override
    {
        std::cout << "exporting Word to JSON" << std::endl;
    }

    virtual void serialize() const override
    {
        std::cout << "serializing Word" << std::endl;
    }
};