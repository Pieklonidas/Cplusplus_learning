#include <iostream>
#include <map>

std::map<std::pair<int, int>, long long int> DP;

long long int gridTraveler(int m, int n)
{
    if(m == 1 && n == 1) return 1;
    if(m == 0 || n == 0) return 0;
    if(DP.find(std::make_pair(m, n)) != DP.end()) return DP[std::make_pair(m, n)];

    DP[std::make_pair(m, n)] = gridTraveler(m - 1, n) + gridTraveler(m, n - 1);
    DP[std::make_pair(n, m)] = DP[std::make_pair(m, n)];
    return DP[std::make_pair(m, n)];
}

int main()
{
    std::cout << gridTraveler(1, 1) << std::endl;
    std::cout << gridTraveler(2, 3) << std::endl;
    std::cout << gridTraveler(3, 2) << std::endl;
    std::cout << gridTraveler(3, 3) << std::endl;
    std::cout << gridTraveler(18, 18) << std::endl;

    return 0;
}
