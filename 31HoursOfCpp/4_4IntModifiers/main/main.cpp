#include <iostream>



int main()
{
  /*signed*/int value1{10};
    signed int value2{-300};

    std::cout << "value1: " << value1 << std::endl;
    std::cout << "value2: " << value2 << std::endl;
    std::cout << "sizeof(value1): " << sizeof (value1) << std::endl;
    std::cout << "sizeof(value2): " << sizeof (value2) << std::endl;

    unsigned int value3{4};
    //unsigned int value4{-5}; //ERROR

    //short:

    /*signed/unsigned*/ short /*int*/ short_var{321}; // 2 Bytes

    /*signed/unsigned*/ long /*int*/ long_var{322}; // 4 or 8 bytes

    /*signed/unsigned*/ long long /*int*/ long_long_var{323}; // 8 bytes

    std::cout << "Short variable: " << short_var << " , size: " << sizeof (short) << " bytes" << std::endl;
    std::cout << "Long variable: " << long_var << " , size: " << sizeof (long) << " bytes" << std::endl;
    std::cout << "Long long variable: " << long_long_var << " , size: " << sizeof (long long) << " bytes" << std::endl;

    return 0;
}
