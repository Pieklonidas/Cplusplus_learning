#include <iostream>
#include <vector>
#include <map>

std::vector<std::vector<std::string>> allConstruct(std::string target, std::vector<std::string> wordbank, std::map<std::string, std::vector<std::vector<std::string>>>& DP)
{
    if(DP.find(target) != DP.end()) return DP[target];
    if(target.empty()) return {{}};

    std::vector<std::vector<std::string>> result = {};

    for(auto& word : wordbank)
    {
        if(target.find(word) == 0)
        {
            std::string suffix;
            if(target.size() > word.size())
            {
                suffix = target.substr(word.size());
            }
            else if(target.size() == word.size() && target == word)
            {
                suffix = "";
            }
            std::vector<std::vector<std::string>> suffixWays = allConstruct(suffix, wordbank, DP);
            for(auto& way : suffixWays)
            {
                way.emplace(way.begin(), word);
                result.push_back(way);
            }
        }
    }

    DP[target] = result;
    return result;
}

int main()
{
    std::map<std::string, std::vector<std::vector<std::string>>> DP;

    std::vector<std::vector<std::string>> temp = allConstruct("purple", {"purp", "p", "ur", "le", "purpl"}, DP);

    for(const auto& ways : temp)
    {
        for(const auto& way : ways)
        {
            std::cout << way << ", ";
        }
        std::cout << std::endl;
    }

    DP.clear();

    temp = allConstruct("abcdef", {"cd", "abc", "ab", "def", "abcd", "ef", "c"}, DP);

    for(const auto& ways : temp)
    {
        for(const auto& way : ways)
        {
            std::cout << way << ", ";
        }
        std::cout << std::endl;
    }

    DP.clear();

    temp = allConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, DP);

    for(const auto& ways : temp)
    {
        for(const auto& way : ways)
        {
            std::cout << way << ", ";
        }
        std::cout << std::endl;
    }

    DP.clear();

    temp = allConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, DP);

    for(const auto& ways : temp)
    {
        for(const auto& way : ways)
        {
            std::cout << way << ", ";
        }
        std::cout << std::endl;
    }

    DP.clear();

    temp = allConstruct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
                             {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, DP);

    for(const auto& ways : temp)
    {
        for(const auto& way : ways)
        {
            std::cout << way << ", ";
        }
        std::cout << std::endl;
    }

    DP.clear();

    temp = allConstruct("konstantynopolitanczykowianeczka",
                       {"k", "konst", "nstan", "ons", "ta", "ntyn", "p", "o", "li", "ncz", "ykow", "a", "ian", "eczk", "polit", "nt", "stan"}, DP);

    for(const auto& ways : temp)
    {
        for(const auto& way : ways)
        {
            std::cout << way << ", ";
        }
        std::cout << std::endl;
    }

    DP.clear();

    temp = allConstruct("konstantynopolitanczykowianeczka",
                       {"k", "konst", "nstan", "ons", "ta", "ntyn", "p", "o", "li", "ncz", "ykow", "ian", "eczk", "polit", "nt", "stan"}, DP);

    for(const auto& ways : temp)
    {
        for(const auto& way : ways)
        {
            std::cout << way << ", ";
        }
        std::cout << std::endl;
    }

    DP.clear();

    return 0;
}
