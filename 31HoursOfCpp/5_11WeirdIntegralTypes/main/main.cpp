#include <iostream>

int main()
{
    short int value1{10};
    short int value2{20};

    char var1{40};
    char var2{50};

    std::cout << "Size of value1: " << sizeof (value1) << std::endl;
    std::cout << "Size of value2: " << sizeof (value2) << std::endl;
    std::cout << "Size of var1: " << sizeof (var1) << std::endl;
    std::cout << "Size of var2: " << sizeof (var2) << std::endl;

    auto result1 = var1 + var2;
    auto result2 = value1 + value2;

    short int value3 = value1 + value2;
    char var3 = var1+var2;

    std::cout << "value3: " << value3 << std::endl;
    std::cout << "Size of value3: " << sizeof (value3) << std::endl;
    std::cout << "var3: " << var3 << std::endl;
    std::cout << "Size of var3: " << sizeof (var3) << std::endl;
    std::cout << "Size of result1: " << sizeof (result1) << std::endl;
    std::cout << "Size of result2: " << sizeof (result2) << std::endl;
    std::cout << "result1: " << result1 << std::endl;
    std::cout << "result2: " << result2 << std::endl;
    std::cout << "var1: " << var1 << std::endl;
    std::cout << "var2: " << var2 << std::endl;
    return 0;
}
