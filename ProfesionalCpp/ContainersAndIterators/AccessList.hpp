#pragma once

#include <set>
#include <string>
#include <string_view>
#include <vector>

class AccessList
{
public:
    AccessList() = default;
    AccessList(std::initializer_list<std::string_view> initList);
    void addUser(std::string_view user);
    void removeUser(std::string_view user);
    bool isAllowed(std::string_view user) const;
    std::vector<std::string> getAllUsers() const;
private:
    std::set<std::string> mAllowed;
};

