#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>

bool perfectScore(int num)
{
    return (num >= 100);
}

void findExample()
{
    int num;
    std::vector<int> myVector;
    while(true)
    {
        std::cout << "Enter a number to add (0 to stop): ";
        std::cin >> num;
        if(num == 0)
        {
            break;
        }
        myVector.push_back(num);
    }

    {
        auto endIt = cend(myVector);
        auto it = find_if(cbegin(myVector), endIt, perfectScore); // ADL
        if (it == endIt)
        {
            std::cout << "No perfect scores" << std::endl;
        }
        else
        {
            std::cout << "Found a perfect score of " << *it << std::endl;
        }
    }

    {
        double sum = std::accumulate(cbegin(myVector), cend(myVector), 0.0);
        std::cout << "The arithmetic mean is: " << sum / myVector.size() << std::endl;
        double mult = std::accumulate(cbegin(myVector), cend(myVector), 1.0, 
                      [](const int num1, const int num2){ return num1*num2; });
        std::cout << "The geometric mean is: " << std::pow(mult, 1.0 / myVector.size()) << std::endl;
    }

    while(true)
    {
        std::cout << "Enter a number to lookup (0 to stop): ";
        std::cin >> num;
        if(num == 0)
        {
            break;
        }
        auto endIt = cend(myVector);
        auto it = std::find(cbegin(myVector), endIt, num);
        if(it == endIt)
        {
            std::cout << "Could not find " << num << std::endl;
        }
        else
        {
            std::cout << "Found " << *it << std::endl;
        }
    }
}

int main()
{
    findExample();
    return 0;
}