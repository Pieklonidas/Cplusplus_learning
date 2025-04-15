#pragma once

#include "DecoratedItem.hpp"
#include <cmath>

class Taxed : public DecoratedItem
{
public:
    Taxed(double taxRate, std::unique_ptr<Item> item)
        : DecoratedItem(std::move(item)), factor_(1.0+taxRate)
    {
        if( !std::isfinite(taxRate) || taxRate < 0.0 ) {
            throw std::invalid_argument( "Invalid taxRate" );
         }
    }

    Money price() const override
    {
        return item().price()*factor_;
    }

private:
    double factor_;
};