#pragma once

#include "Engine.hpp"

class ElectricEngine : public Engine
{
public:
    void start() override;
    void stop() override;
};