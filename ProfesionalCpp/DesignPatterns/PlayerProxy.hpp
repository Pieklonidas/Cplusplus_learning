#pragma once
#include "IPlayer.hpp"
#include <memory>

class PlayerProxy : public IPlayer
{
public:
    PlayerProxy(std::unique_ptr<IPlayer> player);
    virtual std::string getName() const override;
    virtual std::string sendInstantMessage(std::string_view message) const override;

    static inline bool connected = true;
private:
    std::unique_ptr<IPlayer> mPlayer;
};

bool hasNetworkConnectivity();