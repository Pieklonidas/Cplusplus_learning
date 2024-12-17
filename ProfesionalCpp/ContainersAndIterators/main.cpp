#include <iostream>
#include <vector>
#include <limits>

void vectorExample1()
{
    std::vector<double> doubleVector{123.451, 365.12, 2134.165, 823.832, 12.34};
    double max = -std::numeric_limits<double>::infinity();

    for(size_t i = 0; i < doubleVector.size(); i++)
    {
        if(doubleVector[i] > max)
        {
            max = doubleVector[i];
        }
    }

    max /= 100.0;
    for(auto& element : doubleVector)
    {
        element /= max;
        std::cout << element << " ";
    }

    std::cout << std::endl;
}

void vectorExample2()
{
    std::vector<double> doubleVector;
    double max = -std::numeric_limits<double>::infinity();

    for(size_t i = 0; true; i++)
    {
        double temp;
        std::cout << "Enter score " << i << " (-1 to stop): ";
        std::cin >> temp;
        if(temp == -1)
        {
            break;
        }
        doubleVector.push_back(temp);
        if(temp > max)
        {
            max = temp;
        }
    }

    max /= 100.0;
    for(auto& element : doubleVector)
    {
        element /= max;
        std::cout << element << " ";
    }

    std::cout << std::endl;
}

void vectorExample3()
{
    std::vector<int> vectorOne(10);
    std::vector<int> vectorTwo(10);

    if(vectorOne == vectorTwo)
    {
        std::cout << "Equal!\n";
    }
    else
    {
        std::cout << "Not equal!\n";
    }
    
    vectorOne[3] = 50;

    if(vectorOne < vectorTwo)
    {
        std::cout << "vectorOne is less than vectorTwo\n";
    }
    else
    {
        std::cout << "vectorOne is not less than vectorTwo\n";
    }

    std::vector<int> vectorThree(11);
    if(vectorThree > vectorTwo)
    {
        std::cout << "vectorThree is greater than vectorTwo\n";
    }
    else
    {
        std::cout << "vectorThree is less than vectorTwo\n";
    }
}

int main()
{
    // vectorExample1();
    // vectorExample2();
    vectorExample3();
    return 0;
}