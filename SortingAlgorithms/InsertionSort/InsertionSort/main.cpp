#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

void insertionSort(std::vector<int>& arr)
{
    int n = (int)arr.size();
    int current;
    int otherIndex;
    for(int i = 1; i < n; i++)
    {
        current = arr[i];
        otherIndex = i;
        while (otherIndex>0 && current < arr[otherIndex-1])
        {
            arr[otherIndex] = arr[otherIndex-1];
            otherIndex--;
        }
        arr[otherIndex] = current;
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
    insertionSort(arr);

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

















