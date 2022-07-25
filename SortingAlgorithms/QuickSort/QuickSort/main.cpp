#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int chosePivot(std::vector<int>& array, int left, int right)
{
    int mid = left+(right-left)/2;
    int pivotValue = array[mid];
    int temp = array[mid];
    array[mid] = array[right];
    array[right] = temp;
    return array[right];
    return pivotValue;
}

int partitionArray(std::vector<int>& array, int left, int right)
{
    int pivotValue = chosePivot(array, left, right);
    int border = left - 1;
    int i = left;

    while(i < right)
    {
        if(array[i] < pivotValue)
        {
            border++;
            if(border != i)
            {
                int temp = array[border];
                array[border] = array[i];
                array[i] = temp;
            }
        }
        i++;
    }
    border++;
    if(border != right)
    {
        int temp = array[border];
        array[border] = array[right];
        array[right] = temp;
    }
    return border;
}

void quickSort(std::vector<int>& array, int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int border = partitionArray(array, left, right);
    if(border - left < right - border)
    {
        quickSort(array, left, border-1);
        quickSort(array, border+1, right);
    }
    else
    {
        quickSort(array, border+1, right);
        quickSort(array, left, border-1);
    }
}

int main()
{
    int size_of_array = 200;
    std::vector<int> arr(size_of_array);
    int max = size_of_array*2;
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
    quickSort(arr, 0, size_of_array-1);

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

















