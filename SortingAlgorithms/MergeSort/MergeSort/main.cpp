#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

void Merge(std::vector<int> &array, int left_index, int middle_index, int right_index)
{
    std::vector<int> extra = array;

    int finger1 = left_index;
    int finger2 = middle_index + 1;
    int current = left_index;

    while (finger1 <= middle_index && finger2 <= right_index)
    {
        if(extra[finger1] <= extra[finger2])
        {
            array[current] = extra[finger1];
            finger1++;
        }
        else
        {
            array[current] = extra[finger2];
            finger2++;
        }
        current++;
    }
    while (finger1 <= middle_index)
    {
        array[current] = extra[finger1];
        current++; finger1++;
    }
}

void MergeSort(std::vector<int> &array, int left_index, int right_index)
{
    if(left_index < right_index)
    {
        int middle = (left_index + right_index) / 2;
        MergeSort(array, left_index, middle);
        MergeSort(array, middle+1, right_index);
        Merge(array, left_index, middle, right_index);
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
//    std::cout << "Before: " << std::endl;
//    for(const auto& n : arr)
//    {
//        std::cout << n << " ";
//    }
//    std::cout << std::endl;
    MergeSort(arr, 0, size_of_array-1);

//    std::cout << "After: " << std::endl;
//    for(const auto& n : arr)
//    {
//        std::cout << n << " ";
//    }
//    std::cout << std::endl;

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

















