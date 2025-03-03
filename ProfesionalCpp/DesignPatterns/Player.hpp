#pragma once
#include "IPlayer.hpp"

class Player : public IPlayer
{
public:
    virtual std::string getName() const override;
    virtual std::string sendInstantMessage(std::string_view message) const override;
    static inline bool wannaPlayAgain = true;
};