#include "BuddyList.hpp"

void BuddyList::addBuddy(const std::string& name, const std::string& buddy)
{
    if(!isBuddy(name, buddy))
    {
        mBuddies.insert({ name, buddy });
    }
}

void BuddyList::removeBuddy(const std::string& name, const std::string& buddy)
{
    auto begin = mBuddies.lower_bound(name);
    auto end = mBuddies.upper_bound(name);

    for (auto iter = begin; iter != end; iter++)
    {
        if(iter->second == buddy)
        {
            mBuddies.erase(iter);
            break;
        }
    }
}

bool BuddyList::isBuddy(const std::string& name, const std::string& buddy) const
{
    auto [begin, end] = mBuddies.equal_range(name);
    for(auto iter = begin; iter != end; iter++)
    {
        if(iter->second == buddy)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::string> BuddyList::getBuddies(const std::string& name) const
{
    auto [begin, end] = mBuddies.equal_range(name);
    std::vector<std::string> buddies;
    for(auto iter = begin; iter != end; ++iter)
    {
        buddies.push_back(iter->second);
    }
    return buddies;
}