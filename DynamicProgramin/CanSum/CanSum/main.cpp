#include <iostream>
#include <vector>
#include <map>

bool canSum(int targetSum, std::vector<int> numbers, std::map<int, bool>& DP)
{
    if(DP.find(targetSum) != DP.end()) return DP[targetSum];
    if(targetSum == 0) return true;
    if(targetSum < 0) return false;

    for(auto& num : numbers)
    {
        int remainder = targetSum - num;
        if(canSum(remainder, numbers, DP) == true)
        {
            DP[targetSum] = true;
            return true;
        }
    }

    DP[targetSum] = false;
    return false;
}

int main()
{
    std::map<int, bool> DP;
    if(canSum(7, {2, 3}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canSum(7, {5, 3, 4, 7}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canSum(7, {2, 4}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canSum(8, {2, 3, 5}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canSum(300, {7, 14}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }
    return 0;
}
