#include <iostream>

int main()
{
    int scores[10]; // Junk data
    /*
    for(size_t i{0}; i < 10; ++i)
    {
        std::cout<< "scores[" << i << "]: " << scores[i] << std::endl;
    }
    */
    //write data into an array

    for(size_t i{0}; i < 10; ++i)
    {
        scores[i] = i*10;
    }

    for(size_t i{0}; i < 10; ++i)
    {
        std::cout<< "scores[" << i << "]: " << scores[i] << std::endl;
    }

    std::cout << std::endl;

    double salaries[5] {12.7, 7.5, 13.2, 8.1, 9.3};
    for(size_t i{0}; i < 5; ++i)
    {
        std::cout<< "salaries[" << i << "]: " << salaries[i] << std::endl;
    }

    std::cout << std::endl;

    int families[5] {12, 7, 13};
    for(size_t i{0}; i < 5; ++i)
    {
        std::cout<< "families[" << i << "]: " << families[i] << std::endl;
    }

    std::cout << std::endl;

    int class_sizes[] {12, 7, 13, 3, 2, 13241, 421, 213, 321};
    for(auto value : class_sizes)
    {
        std::cout<< "value: " << value << std::endl;
    }

    const int birds[] {12, 7, 13, 3, 2, 13241, 421, 213, 321};
    //birds[2] = 9; //compiler error

    return 0;
}
