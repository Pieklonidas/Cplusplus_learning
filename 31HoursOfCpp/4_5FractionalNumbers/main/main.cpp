#include <iostream>
#include <iomanip>


int main()
{
    //Declare and initialize the variables
    float number1{1.12345678901234567890f};
    double number2{1.12345678901234567890};
    long double number3{1.12345678901234567890L};

    //Print out the sizes
    std::cout << "sizeof float: " << sizeof (float) << std::endl;
    std::cout << "sizeof double: " << sizeof (double) << std::endl;
    std::cout << "sizeof long double: " << sizeof (long double) << std::endl;

    //Print out numbers
    std::cout << "number1: " << number1 << std::endl;
    std::cout << "number2: " << number2 << std::endl;
    std::cout << "number3: " << number3 << std::endl;

    //Precision 20
    std::cout << "Precision: " << std::endl;
    std::cout << std::setprecision(20);
    std::cout << "number1: " << number1 << std::endl;
    std::cout << "number2: " << number2 << std::endl;
    std::cout << "number3: " << number3 << std::endl;

    //Float problem: The precision is usually too limited
    //for a lot of applications
    float number4{192400023.0f};
    std::cout << "number4: " << number4 << std::endl;

    //Scientific notation

    double number5{192400023};
    double number6{1.92400023e8};
    double number7{1.924e8};

    double number8{0.00000000003498};
    double number9{3.498e-11};
    std::cout << "number5: " << number5 << std::endl;
    std::cout << "number6: " << number6 << std::endl;
    std::cout << "number7: " << number7 << std::endl;
    std::cout << "number8: " << number8 << std::endl;
    std::cout << "number9: " << number9 << std::endl;

    //Infinity and NaN
    std::cout << "\nInfinity and NaN" << std::endl;

    double number10{-5.6};
    double number11{};
    double number12{};

    //Inf
    double result {number10/number11};

    std::cout << number10 << "/" << number11 << " yields " << result << std::endl;
    std::cout <<result << " + " << number10 << " yields " << result + number10 << std::endl;

    //NaN

    result = number11/number12;

    std::cout << number11 << "/" << number12 << " = " << result << std::endl;

    return 0;
}
