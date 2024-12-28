#pragma once

#include <bitset>
#include <string_view>
#include <map>

const size_t kNumChannels = 10;

class CableCompany
{
public:
    void addPackage(std::string_view packageName, const std::bitset<kNumChannels>& channels);
    void removePackage(std::string_view packageName);
    const std::bitset<kNumChannels>& getPackege(std::string_view packageName) const;
    void newCustomer(std::string_view name, std::string_view packageName);
    void newCustomer(std::string_view name, const std::bitset<kNumChannels>& channels);
    void addChannel(std::string_view name, int channel);
    void removeChannel(std::string_view name, int channel);
    void addPackageToCustomer(std::string_view name, std::string_view package);
    void deleteCustomer(std::string_view name);
    const std::bitset<kNumChannels>& getCustomerChannels(std::string_view name) const;
private:
    std::bitset<kNumChannels>& getCustomerChannelsHelper(std::string_view name);
    using MapType = std::map<std::string, std::bitset<kNumChannels>>;
    MapType mPackeges, mCustomers;
};
