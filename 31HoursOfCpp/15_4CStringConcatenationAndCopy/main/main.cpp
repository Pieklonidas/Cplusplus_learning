#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    cout << "std::strcat: " << std::endl;
    char dest[50] = "Hello ";
    char src[50] = "World!";
    std::strcat(dest,src);
    std::cout << "dest: " << dest << std::endl;
    std::strcat(dest, " Goodbye World!");
    std::cout << "dest: " << dest << std::endl;

    cout << endl;

    std::cout << "More std::strcat: " << endl;
    char *dest1 = new char[30]{'F','i','r','e','l','o','r','d','\0'};
    char *src1 = new char[30]{',','T','h','e',' ','P','h','e','n','i','x','\0'};

    cout << "std::strlen(dest1): " << std::strlen(dest1) << endl;
    cout << "std::strlen(src1): " << std::strlen(src1) << endl;

    cout << "Concatenating..." << endl;
    std::strcat(dest1, src1);

    cout << "std::strlen(dest1): " << std::strlen(dest1) << endl;
    cout << "dest1: " << dest1 << endl;

    delete[] dest1;
    delete[] src1;

    cout << endl;
    cout << "std::strncat:" << endl;

    char dest2[50] = "Hello ";
    const char src2[30] = "there is a bird on my window";
    cout << std::strncat(dest2, src2, 6) << endl;
    std::strncat(dest2, src2, 6);
    cout << "dest2: " << dest2 << endl;

    cout << endl;

    std::cout << "More std::strcpy: " << endl;

    const char *src3 = "C++ is a multipurpose programing language";
    char *dest3 = new char[std::strlen(src3) + 1];

    std::strcpy(dest3, src3);

    cout << "sizeof(dest3): " << sizeof(dest3) << endl;
    cout << "std::strlen(dest3): " << std::strlen(dest3) << endl;
    cout << "dest3: " << dest3 << endl;

    delete[] dest3;

    cout << endl;

    std::cout << "More std::strncpy: " << endl;

    const char *src4 = "C++ is a multipurpose programing language";
    char dest4[] = {'a','b','c','e','f','g','\0'};

    std::strncpy(dest4, src4, 5);

    cout << "sizeof(dest4): " << sizeof(dest4) << endl;
    cout << "std::strlen(dest4): " << std::strlen(dest4) << endl;
    cout << "dest4: " << dest4 << endl;

    return 0;
}
