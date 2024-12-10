#include <iostream>


int main()
{
    int scores[]{1,2,3,4,5,6,7,8};

    size_t count {std::size(scores)}; // c++17

    for(size_t i{0}; i < count; ++i)
    {
        std::cout << "scores[" << i << "]: " << scores[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << "sizeof(scores): " << sizeof (scores) << std::endl;
    std::cout << "sizeof(scores[0]): " << sizeof (scores[0]) << std::endl;
    std::cout << "count: " << sizeof (scores) / sizeof(scores[0]) << std::endl;


    size_t count2 {sizeof (scores) / sizeof(scores[0])};

    for(size_t i{0}; i < count2; ++i)
    {
        std::cout << "scores[" << i << "]: " << scores[i] << std::endl;
    }

    std::cout << std::endl;

    for(auto score : scores)
    {
        std::cout << "score: " << score << std::endl;
    }

    return 0;
}
