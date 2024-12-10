#include <iostream>

int main()
{
    int value{5};

    std::cout << "The value is (incrementing): " << value++ << std::endl;
    std::cout << "The value is: " << value << std::endl;

    value = 5;

    std::cout << "The value is (decrementing): " << value-- << std::endl;
    std::cout << "The value is: " << value << std::endl;

    value = 5;

    std::cout << "The value is (prefix inc): " << ++value << std::endl;

    value = 5;

    std::cout << "The value is (prefix dec): " << --value << std::endl;

    return 0;
}
