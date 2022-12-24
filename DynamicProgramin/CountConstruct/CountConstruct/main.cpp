#include <iostream>
#include <vector>
#include <map>

int countConstruct(std::string target, std::vector<std::string> wordbank, std::map<std::string, int>& DP)
{
    if(DP.find(target) != DP.end()) return DP[target];
    if(target.empty()) return 1;

    int totalCount = 0;

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
            int numWays = countConstruct(suffix, wordbank, DP);
            totalCount += numWays;
        }
    }


    DP[target] = totalCount;
    return totalCount;
}

int main()
{
    std::map<std::string, int> DP;

    std::cout << countConstruct("purple", {"purp", "p", "ur", "le", "purpl"}, DP) << std::endl;

    DP.clear();

    std::cout << countConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}, DP) << std::endl;

    DP.clear();

    std::cout << countConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, DP) << std::endl;

    DP.clear();

    std::cout << countConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, DP) << std::endl;

    DP.clear();

    std::cout << countConstruct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
                             {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, DP) << std::endl;
    DP.clear();

    std::cout << countConstruct("konstantynopolitanczykowianeczka",
                             {"k", "konst", "nstan", "ons", "ta", "ntyn", "p", "o", "li", "ncz", "ykow", "a", "ian", "eczk", "polit", "nt", "stan"}, DP) << std::endl;
    DP.clear();

       std::cout << countConstruct("konstantynopolitanczykowianeczka",
                                 {"k", "konst", "nstan", "ons", "ta", "ntyn", "p", "o", "li", "ncz", "ykow", "ian", "eczk", "polit", "nt", "stan"}, DP) << std::endl;
    DP.clear();

    return 0;
}
