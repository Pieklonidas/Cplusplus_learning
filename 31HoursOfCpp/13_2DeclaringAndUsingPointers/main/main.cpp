#include <iostream>


int main()
{
    int* p_number{nullptr};
    double* p_fractional_number{nullptr};

    std::cout << "sizeof(int): " << sizeof(int) << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << std::endl;
    std::cout << "sizeof(int*): " << sizeof(int*) << std::endl;
    std::cout << "sizeof(double*): " << sizeof(double*) << std::endl;
    std::cout << "sizeof(p_number): " << sizeof(p_number) << std::endl;
    std::cout << "sizeof(p_fractional_number): " << sizeof(p_fractional_number) << std::endl;

    std::cout << std::endl;
    int* p_number5{}, other_int_var5{};
    std::cout << "sizeof(p_number5): " << sizeof(p_number5) << std::endl;
    std::cout << "sizeof(other_int_var5): " << sizeof(other_int_var5) << std::endl;

    std::cout << std::endl;
    int int_var{43};
    int* p_int{&int_var};

    std::cout << "Int var: " << int_var << std::endl;
    std::cout << "p_int (Address in memory): " << p_int << std::endl;

    int int_var1{65};
    p_int = &int_var1;
    std::cout << "p_int (with different address): " << p_int << std::endl;

    std::cout << std::endl;

    int* p_int2{nullptr};
    int int_data{56};
    p_int2 = &int_data;

    std::cout << "value: " << *p_int2 << std::endl;

    return 0;
}
