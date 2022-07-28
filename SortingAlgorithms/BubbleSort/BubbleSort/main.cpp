#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

void swap(std::vector<int>& arr, int index1, int index2)
{
    int tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}

void bubbleSort(std::vector<int>& arr)
{
    int n = (int)arr.size();
    int it = 0;
    bool swapped = true;
    while(it < n-1 && swapped)
    {
        swapped = false;
        for(int j = 0; j < n-1-it; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr, j, j+1);
                swapped = true;
            }
        }
        it++;
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
    bubbleSort(arr);

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

















