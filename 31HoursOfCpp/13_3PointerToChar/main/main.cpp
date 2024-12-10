#include <iostream>

int main()
{
    const char* message{"Hello World!"};
    std::cout << "message: " << message << std::endl;
    std::cout << std::endl;
    std::cout << "*message: " << *message << std::endl;


    return 0;
}
