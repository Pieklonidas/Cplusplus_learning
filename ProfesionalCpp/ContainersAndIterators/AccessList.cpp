#include "AccessList.hpp"

AccessList::AccessList(std::initializer_list<std::string_view> initList)
{
    mAllowed.insert(begin(initList), end(initList));
}

void AccessList::addUser(std::string_view user)
{
    mAllowed.emplace(user);
}

void AccessList::removeUser(std::string_view user)
{
    mAllowed.erase(std::string(user));
}

bool AccessList::isAllowed(std::string_view user) const
{
    return (mAllowed.count(std::string(user)) != 0);
}

std::vector<std::string> AccessList::getAllUsers() const
{
    return { begin(mAllowed), end(mAllowed) };
}