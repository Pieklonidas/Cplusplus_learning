#pragma once

#include <map>
#include <vector>
#include <string>

class BuddyList
{
public:
    void addBuddy(const std::string& name, const std::string& buddy);
    void removeBuddy(const std::string& name, const std::string& buddy);
    bool isBuddy(const std::string& name, const std::string& buddy) const;
    std::vector<std::string> getBuddies(const std::string& name) const;
private:
    std::multimap<std::string, std::string> mBuddies;
};
