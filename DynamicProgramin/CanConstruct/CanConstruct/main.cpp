#include <iostream>
#include <vector>
#include <map>

bool canConstruct(std::string target, std::vector<std::string> wordbank, std::map<std::string, bool>& DP)
{
    if(DP.find(target) != DP.end()) return DP[target];
    if(target.empty()) return true;

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
            if(canConstruct(suffix, wordbank, DP) == true)
            {
                DP[target] = true;
                return true;
            }
        }
    }


    DP[target] = false;
    return false;
}

int main()
{
    std::map<std::string, bool> DP;
    if(canConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canConstruct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
                    {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canConstruct("konstantynopolitanczykowianeczka",
                    {"k", "konst", "nstan", "ons", "ta", "ntyn", "p", "o", "li", "ncz", "ykow", "a", "ian", "eczk", "polit", "nt", "stan"}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    if(canConstruct("konstantynopolitanczykowianeczka",
                    {"k", "konst", "nstan", "ons", "ta", "ntyn", "p", "o", "li", "ncz", "ykow", "ian", "eczk", "polit", "nt", "stan"}, DP))
    {
       std::cout << "Possible" << std::endl;
    }
    else
    {
        std::cout << "Not possible" << std::endl;
    }

    DP.clear();

    return 0;
}
