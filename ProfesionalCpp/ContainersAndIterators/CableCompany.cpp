#include "CableCompany.hpp"

#include <stdexcept>

void CableCompany::addPackage(std::string_view packageName, const std::bitset<kNumChannels>& channels)
{
    mPackeges.emplace(packageName, channels);
}

void CableCompany::removePackage(std::string_view packageName)
{
    mPackeges.erase(packageName.data());
}

const std::bitset<kNumChannels>& CableCompany::getPackege(std::string_view packageName) const
{
    auto it = mPackeges.find(packageName.data());
    if(it == end(mPackeges))
    {
        throw std::out_of_range("Invalid package");
    }
    return it->second;
}

void CableCompany::newCustomer(std::string_view name, std::string_view packageName)
{
    auto& packageChannels = getPackege(packageName);
    newCustomer(name, packageChannels);
}

void CableCompany::newCustomer(std::string_view name, const std::bitset<kNumChannels>& channels)
{
    auto result = mCustomers.emplace(name, channels);
    if(!result.second)
    {
        throw std::invalid_argument("Duplicate customer");
    }
}

void CableCompany::addChannel(std::string_view name, int channel)
{
    auto& customerChannels = getCustomerChannelsHelper(name);
    customerChannels.set(channel);
}

void CableCompany::removeChannel(std::string_view name, int channel)
{
    auto& customerChannels = getCustomerChannelsHelper(name);
    customerChannels.reset(channel);
}

void CableCompany::addPackageToCustomer(std::string_view name, std::string_view package)
{
    auto& packageChannels = getPackege(package);
    auto& customerChannels = getCustomerChannelsHelper(name);
    customerChannels |= packageChannels;
}

void CableCompany::deleteCustomer(std::string_view name)
{
    mCustomers.erase(name.data());
}
const std::bitset<kNumChannels>& CableCompany::getCustomerChannels(std::string_view name) const
{
    return const_cast<CableCompany*>(this)->getCustomerChannelsHelper(name);
}
std::bitset<kNumChannels>& CableCompany::getCustomerChannelsHelper(std::string_view name)
{
    auto it = mCustomers.find(name.data());
    if (it == end(mCustomers))
    {
        throw std::invalid_argument("Uknown customer");
    }
    return it->second;
}