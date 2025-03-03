#include "PlayerProxy.hpp"

PlayerProxy::PlayerProxy(std::unique_ptr<IPlayer> player)
    : mPlayer(std::move(player))
{
}

std::string PlayerProxy::getName() const
{
    return std::string("PlayerProxy");
}

std::string PlayerProxy::sendInstantMessage(std::string_view message) const
{
    if(hasNetworkConnectivity())
        return mPlayer->sendInstantMessage(message);
    else
        return "offline";
}

bool hasNetworkConnectivity()
{
    return PlayerProxy::connected;
}