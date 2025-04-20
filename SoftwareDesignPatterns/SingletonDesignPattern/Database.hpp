#pragma once

#include <iostream>
#include "PersistenceInterface.hpp"

class Database : public PersistenceInterface
{
public:
    Database() = default;

    Database(const Database&) = delete;
    Database& operator==(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator==(Database&&) = delete;
private:
    bool do_read() const override
    {
        std::cout << "reading" << std::endl;
        return true;
    }
    bool do_write() override
    {
        std::cout << "writing" << std::endl;
        return true;
    }
};