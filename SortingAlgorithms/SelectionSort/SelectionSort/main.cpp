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

void selectionSort(std::vector<int>& arr)
{
    int n = (int)arr.size();
    int minIndex = 0;
    for(int i = 0; i < n - 1; i++)
    {
        minIndex = i;
        for(int j = i+1; j<n; j++)
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if(minIndex != i)
        {
            swap(arr, minIndex, i);
        }
    }
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
    selectionSort(arr);

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

















