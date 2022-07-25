#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

void validateMaxHeap(std::vector<int>& array, int heapSize, int parentIndex)
{
    int maxIndex = parentIndex;
    int leftChild = parentIndex*2+1;
    int rightChild = parentIndex*2+2;
    if(leftChild < heapSize && array[leftChild] > array[maxIndex])
    {
        maxIndex = leftChild;
    }
    if(rightChild < heapSize && array[rightChild] > array[maxIndex])
    {
        maxIndex = rightChild;
    }
    if(maxIndex != parentIndex)
    {
        int temp = array[maxIndex];
        array[maxIndex] = array[parentIndex];
        array[parentIndex] = temp;
        validateMaxHeap(array, heapSize, maxIndex);
    }
}

void heapSort(std::vector<int>& array)
{
    int n = (int)array.size();

    for (int i = n/2-1; i >= 0; i--)
    {
        validateMaxHeap(array, n, i);
    }

    for(int i = n-1; i > 0; i--)
    {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        n--;
        validateMaxHeap(array, n, 0);
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
        heapSort(arr);

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
