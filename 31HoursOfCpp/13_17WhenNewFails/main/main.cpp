#include <iostream>

int main()
{

    for(size_t i{0}; i < 100; ++i)
    {
        try {
            int * data = new int[100000000];
        }  catch (std::exception& ex) {
            std::cout << "Something went wrong: " << ex.what() << std::endl;
        }
    }

    std::cout << "Program is ending well!" << std::endl;

    return 0;
}
