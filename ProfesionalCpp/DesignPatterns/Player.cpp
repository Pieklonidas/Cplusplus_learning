#include "Player.hpp"
#include <iostream>


std::string Player::getName() const
{
    return "Player";
}

std::string Player::sendInstantMessage(std::string_view message) const
{
    std::cout << message << std::endl;
    return Player::wannaPlayAgain ? "yes" : "no";
}