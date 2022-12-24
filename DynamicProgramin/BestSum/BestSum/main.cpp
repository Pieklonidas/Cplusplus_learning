#include <iostream>
#include <map>
#include <vector>

std::map<int, std::optional<std::vector<int>>> DP;

std::optional<std::vector<int>> bestSum(int targetSum, const std::vector<int> numbers)
{
    if(targetSum == 0) return std::vector<int>{};
    if(targetSum < 0) return std::nullopt;
    if(DP.find(targetSum) != DP.end()) return DP[targetSum];

    std::optional<std::vector<int>> shortestCombination = std::nullopt;

    for(auto num : numbers)
    {
        const auto reminder = targetSum - num;
        auto result = bestSum(reminder, numbers);
        if (result)
        {
            result->push_back(num);
            // if the combination is shorter than the current "shortest", update it
            if(!shortestCombination || result->size() < shortestCombination->size())
            {
                shortestCombination = result;
            }
        }
    }
    DP[targetSum] = shortestCombination;
    return shortestCombination;
}

int main()
{
    std::optional<std::vector<int>> one = bestSum(7, {5, 3, 4, 7});
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

    std::optional<std::vector<int>> two = bestSum(8, {2, 3, 5});
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

    std::optional<std::vector<int>> three = bestSum(8, {1, 4, 5});
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

    std::optional<std::vector<int>> four = bestSum(100, {1, 2, 5, 25});
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

    return 0;
}
