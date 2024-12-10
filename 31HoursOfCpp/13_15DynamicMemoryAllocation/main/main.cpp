#include <iostream>

int main()
{
    int *p_number4{nullptr};
    p_number4 = new int;

    *p_number4 = 77;
    std::cout << "Dynamically allocating memory: " << std::endl;
    std::cout << "*p_number4: " << *p_number4 << std::endl;

    delete p_number4;
    p_number4 = nullptr;

    std::cout << std::endl;

    int *p_number5{new int};
    int *p_number6{new int(22)};
    int *p_number7{new int{23}};

    std::cout << "p_number5: " << p_number5 << std::endl;
    std::cout << "*p_number5: " << *p_number5 << std::endl;

    std::cout << "p_number6: " << p_number6 << std::endl;
    std::cout << "*p_number6: " << *p_number6 << std::endl;

    std::cout << "p_number7: " << p_number7 << std::endl;
    std::cout << "*p_number7: " << *p_number7 << std::endl;

    delete p_number5;
    p_number5 = nullptr;

    delete p_number6;
    p_number6 = nullptr;

    delete p_number7;
    p_number7 = nullptr;

    p_number7 = new int(91);
    std::cout << "p_number7: " << p_number7 << std::endl;
    std::cout << "*p_number7: " << *p_number7 << std::endl;

    p_number5 = new int(81);
    std::cout << "p_number5: " << p_number5 << std::endl;
    std::cout << "*p_number5: " << *p_number5 << std::endl;
    delete p_number5;
    p_number5 = nullptr;

    delete p_number7;
    p_number7 = nullptr;

    return 0;
}
