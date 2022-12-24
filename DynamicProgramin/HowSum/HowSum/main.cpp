#include <iostream>
#include <map>
#include <vector>

std::map<int, std::optional<std::vector<int>>> DP;

std::optional<std::vector<int>> howSum(int targetSum, const std::vector<int> numbers)
{
    if(targetSum == 0) return std::vector<int>{};
    if(targetSum < 0) return std::nullopt;
    if(DP.find(targetSum) != DP.end()) return DP[targetSum];

    for(auto num : numbers)
    {
        const auto reminder = targetSum - num;
        auto result = howSum(reminder, numbers);
        if (result)
        {
            result->push_back(num);
            DP[targetSum] = result;
            return result;
        }
    }
    DP[targetSum] = std::nullopt;
    return std::nullopt;
}

int main()
{
    std::optional<std::vector<int>> one = howSum(7, {2, 3});
    if(one){
        for(const auto& num : *one)
        {
            std::cout << num << std::endl;
        }
    }
    else
    {
        std::cout << "null" << std::endl;
    }
    DP.clear();

    std::cout << std::endl;

    std::optional<std::vector<int>> two = howSum(7, {5, 3, 4, 7});
    if(two){
        for(const auto& num : *two)
        {
            std::cout << num << std::endl;
        }
    }
    else
    {
        std::cout << "null" << std::endl;
    }
    DP.clear();

    std::cout << std::endl;

    std::optional<std::vector<int>> three = howSum(7, {2, 4});
    if(three){
        for(const auto& num : *three)
        {
            std::cout << num << std::endl;
        }
    }
    else
    {
        std::cout << "null" << std::endl;
    }
    DP.clear();

    std::cout << std::endl;

    std::optional<std::vector<int>> four = howSum(8, {2, 3, 5});
    if(four){
        for(const auto& num : *four)
        {
            std::cout << num << std::endl;
        }
    }
    else
    {
        std::cout << "null" << std::endl;
    }
    DP.clear();

    std::cout << std::endl;

    std::optional<std::vector<int>> five = howSum(300, {7, 14, 30});
    if(five){
        for(const auto& num : *five)
        {
            std::cout << num << std::endl;
        }
    }
    else
    {
        std::cout << "null" << std::endl;
    }

    return 0;
}
