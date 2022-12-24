#include <iostream>
#include <map>

std::map<int, long long int> DP;

long long int fib(int n)
{
    if( n <= 2) return 1;
    if(DP.find(n) != DP.end())
    {
        return DP[n];
    }
    else
    {
       DP[n] = fib(n-1) + fib(n-2);
       return DP[n];
    }
}

int main()
{
    std::cout << fib(50) << std::endl;
    return 0;
}
