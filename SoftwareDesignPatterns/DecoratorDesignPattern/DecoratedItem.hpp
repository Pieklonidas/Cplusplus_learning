#pragma once

#include "Item.hpp"
#include <memory>
#include <stdexcept>
#include <utility>

class DecoratedItem : public Item
{
public:
    explicit DecoratedItem( std::unique_ptr<Item> item )
        : item_(std::move(item))
    {
        if(!item_)
        {
            throw std::invalid_argument("Invalid item");
        }
    }

protected:
    Item& item() { return *item_; }
    const Item& item() const { return *item_; }

private:
    std::unique_ptr<Item> item_;
};