#include <iostream>

int main()
{
    int max{};

    int a{35};
    int b{20};

    max = (a > b) ? a : b;

    std::cout << "max: " << max << std::endl;

    auto max1 = (a < b) ? a : 22.5f;

    std::cout << "max1: " << max1 << std::endl;

    return 0;
}
