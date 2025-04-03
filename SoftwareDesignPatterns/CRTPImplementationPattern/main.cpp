#include <iostream>
#include "Distances.hpp"
#include "Person.hpp"

int main()
{
    const auto m1 = Meter<long>{ 100l };
    const auto m2 = Meter<long>{ 150l };

    const auto m3 = m1 + m2;
    auto m4 = Meter<long>{ 20l };
    m4 += m2;

    std::cout << "Meters: " << m3 << std::endl;
    std::cout << "Meters: " << m4 << std::endl;

    const auto surname = Surname{ "Placeholder" };

    std::cout << "Surname: " << surname << std::endl;

    return 0;
}