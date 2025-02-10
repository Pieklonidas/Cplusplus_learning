#include <iostream>

int triangularNumbers(int n)
{
    return (n*(n+1))/2;
}

void isASquareNumber(int n)
{
    bool isSquare = false;
    int sum = 1;
    int nextOdd = 3;
    while(n >= sum)
    {
        if(sum == n)
        {
            isSquare = true;
        }
        sum += nextOdd;
        nextOdd += 2;
    }
    std::cout << n << (isSquare ? " is square" : " isn't square") << std::endl;
}

void theSumOfTheReciprocals(int n)
{
    double sum = 0;
    for(int i = 1; i <= n; ++i)
    {
        double triangularNumber = static_cast<double>(triangularNumbers(i));
        sum += 1.0/triangularNumber;
    }
    std::cout << "The sum of the reciprocals: " << sum << std::endl;
}

int main()
{
    std::cout << "The 100th triangular number is" << triangularNumbers(100) << std::endl;
    isASquareNumber(900);
    isASquareNumber(290);
    isASquareNumber(1);
    
    theSumOfTheReciprocals(10);
    theSumOfTheReciprocals(100);
    theSumOfTheReciprocals(10000);

    return 0;
}