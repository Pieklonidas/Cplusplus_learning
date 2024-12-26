#include "BankAccount.hpp"
#include <stdexcept>

bool BankDB::addAccount(const BankAccount& acct)
{
    auto [_, res] = mAccounts.emplace(acct.getAcctNum(), acct);
    return res;
}

void BankDB::deleteAccount(int acctNum)
{
    mAccounts.erase(acctNum);
}

BankAccount& BankDB::findAccount(int acctNum)
{
    auto it = mAccounts.find(acctNum);
    if (it == mAccounts.end())
    {
        throw std::out_of_range("No account with that number.");
    }
    return it->second;
}

BankAccount& BankDB::findAccount(std::string_view name)
{
    for(auto& [_, account] : mAccounts)
    {
        if(account.getClientName() == name)
        {
            return account;
        }
    }
    throw std::out_of_range("No account with that number.");
}

void BankDB::mergeDatabase(BankDB& db)
{
    mAccounts.merge(db.mAccounts);
    db.mAccounts.clear();
}