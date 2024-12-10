#include <iostream>

int main()
{
    //declare array
    char message[6] = {'H', 'e','l','l','o','\0'};

    std::cout << "Message: ";
    for(auto c : message)
    {
        std::cout << c;
    }
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << "message: " << message << std::endl;

    //If a character array is null terminated, it's called as C-String
    std::cout << std::endl;
    char message1[] {'H', 'e','l','l','o','\0'};
    std::cout << "message1: " << message1 << std::endl;


    std::cout << std::endl;
    char message2[6] {'H', 'e','l','l','o'};
    std::cout << "message2: " << message2 << std::endl;
    std::cout << "sizeof(message2): " << sizeof (message2) << std::endl;

    std::cout << std::endl;
    char message4[] {"Hello"};
    std::cout << "message4: " << message4 << std::endl;
    std::cout << "sizeof(message4): " << sizeof (message4) << std::endl;

    std::cout << std::endl;
    char message5[] {"Hello"};
    std::cout << "message4: " << message5 << std::endl;
    std::cout << "sizeof(message4): " << sizeof (message5) << std::endl;

    std::cout << std::endl;
    int numbers [] {1,2,3,4,5};
    std::cout << "numbers: " << numbers << std::endl;
    return 0;
}
