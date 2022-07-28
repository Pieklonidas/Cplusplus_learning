#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <math.h>
#include <vector>

void swap(std::vector<int>& arr, int index1, int index2)
{
    int tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}

void shellSort(std::vector<int>& arr, std::function<std::vector<int>(int)> distGenerator)
{
    int n = (int)arr.size();
    int iter = 1;
    std::vector<int> distances = distGenerator(n);
    int distance = distances[distances.size()-1];
    int current, otherIndex;
    while (distance >= 1)
    {
        for(int i = distance; i < n; i++)
        {
            current = arr[i];
            otherIndex = i;
            while (otherIndex >= distance && current < arr[(otherIndex - distance)%n])
            {
                arr[otherIndex] = arr[otherIndex - distance];
                otherIndex -= distance;
            }
            arr[otherIndex] = current;
        }
        distance = distances[distances.size() - ++iter];
    }
}

std::vector<int> shellDistance(int numberOfElements)
{
    std::vector<int> distances;
    int iteration = 1;
    int generated;
    do{
        generated = numberOfElements / (int)std::pow(2, iteration);
        distances.push_back(generated);
        iteration++;
    }while (generated>0);
    std::reverse(distances.begin(), distances.end());
    return distances;
}

//4^k + 3*2^(k-1) + 1
std::vector<int> sedgewickDistance(int numberOfElements)
{
    std::vector<int> distances;
    int generated = 0;
    int k = 0;
    while (generated < numberOfElements)
    {
        if(distances.empty())
        {
            distances.push_back(0);
            distances.push_back(1);
        }
        else
        {
            generated = (int)(std::pow(4,k) + 3*std::pow(2,k-1) + 1);
            if(generated < numberOfElements)
            {
                distances.push_back(generated);
            }
        }
        k++;
    }
    return distances;
}

int main()
{
    int size_of_array = 200;
    std::vector<int> arr(size_of_array);
    int max = size_of_array*1.5;
    std::srand(time(NULL));
    for(int i = 0; i < size_of_array; i++)
    {
        arr[i] = rand()%max;
    }
    std::cout << "Before: " << std::endl;
    for(const auto& n : arr)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    shellSort(arr, shellDistance);

    std::cout << "After: " << std::endl;
    for(const auto& n : arr)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // For much more size of array:
    bool good = true;
    for(int i = 0; i < size_of_array-1; i++)
    {
        if(arr[i] > arr[i+1])
        {
            good = false;
            break;
        }
    }

    if(good)
    {
        std::cout << "good" << std::endl;
    }
    else
    {
        std::cout << "fail" << std::endl;
    }

    return 0;
}

















