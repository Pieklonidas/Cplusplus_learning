#pragma once

#include "OpenPages.hpp"
#include "Document.hpp"

class Pages : public Document
{
public:
    virtual void exportToJSON() const override
    {
        exportToJSONFormat(pages);
    }

    virtual void serialize() const override
    {
        pages.convertToBytes();
    }

private:
    OpenPages pages;
};