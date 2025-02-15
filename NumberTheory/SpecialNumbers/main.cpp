#include <iostream>
#include <cmath>

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

bool isASquareNumberFaster(int n)
{
    int sqrtOfN = std::sqrt(n);
    return sqrtOfN*sqrtOfN == n;
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

int calculateNFromTriangularNumber(int tn)
{
    int delta = 1+8*tn;
    if(!isASquareNumberFaster(delta)) return - 1;
    return (std::sqrt(delta)-1)/2;
}

void isTriangularNumberExample(int tn)
{
    int n = calculateNFromTriangularNumber(tn);
    if(n >= 0)
    {
        std::cout << tn << " is a triangular number! n = " << n << " |===| Prove (n*(n+1))/2 = " << triangularNumbers(n) << std::endl;
        return;
    }
    std::cout << tn << " is not a triangular number" << std::endl;
}

void find100TriangularAndSquareNumbers()
{
    int index = 0;
    int n = 1;
    while(index < 100)
    {
        int tn = triangularNumbers(n);
        ++n;
        if(isASquareNumberFaster(tn)) 
        {
            std::cout << tn << " is a triangular and square number" << std::endl;
            ++index;
        }
    }
}

void findTraingularNumbersThatAreSumOfOthers()
{
    int howManyNumbers = 0;
    for(int i = 2; i <= 1000; ++i)
    {
        int tn = triangularNumbers(i);
        for(int j = 1; j < i; ++j)
        {
            bool found = false;
            int tn2 = triangularNumbers(j);
            for(int k = 1; k <= j; ++k)
            {
                int tn3 = triangularNumbers(k);
                if(tn == tn2+tn3)
                {
                    std::cout << tn << " is a sum of: " << tn2 << " + " << tn3 << std::endl;
                    howManyNumbers++;
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
    }
    std::cout << "How many numbers: " << howManyNumbers << std::endl;
}

int main()
{
    // std::cout << "The 100th triangular number is" << triangularNumbers(100) << std::endl;
    // isASquareNumber(900);
    // isASquareNumber(290);
    // isASquareNumber(1);
    
    // theSumOfTheReciprocals(10);
    // theSumOfTheReciprocals(100);
    // theSumOfTheReciprocals(10000);

    // isTriangularNumberExample(15);
    // isTriangularNumberExample(21);
    // isTriangularNumberExample(21-15);
    // isTriangularNumberExample(21+15);
    // isTriangularNumberExample(780);
    // isTriangularNumberExample(990);
    // isTriangularNumberExample(990-780);
    // isTriangularNumberExample(990+780);
    // isTriangularNumberExample(123);

    // find100TriangularAndSquareNumbers();
    findTraingularNumbersThatAreSumOfOthers();

    return 0;
}