#include <iostream>

int main()
{
    size_t size = 10;

    double *p_salaries{new double[size]};

    for(size_t i = 0; i < size; i++)
    {
        std::cout << "Salaries " << p_salaries[i] << std::endl;
    }

    int *p_students{new(std::nothrow) int[size]{}};

    for(size_t i = 0; i < size; i++)
    {
        std::cout << "Students " << p_students[i] << std::endl;
    }

    double *p_scores{new(std::nothrow) double[size]{1,2,3,4,5}};
    if(p_scores)
    {
        std::cout << "size of scores (it's a regular pointer): " << sizeof (p_scores) << std::endl;

        for(size_t i = 0; i < size; i++)
        {
            std::cout << "Scores " << p_scores[i] << " : " << *(p_scores + i) << std::endl;
        }
    }

    delete [] p_salaries;
    p_salaries = nullptr;

    delete [] p_students;
    p_students = nullptr;

    delete [] p_scores;
    p_scores = nullptr;

    return 0;
}
