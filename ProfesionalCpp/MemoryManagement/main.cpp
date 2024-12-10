#include <iostream>
#include <memory>

class Simple
{
public:
    Simple() { std::cout << "Constructor of Simple\n"; }
    ~Simple() { std::cout << "Destructor of Simple\n"; }
};

std::unique_ptr<Simple> create()
{
    auto ptr = std::make_unique<Simple>();
    // Do something with ptr…
    return ptr;
}

int main()
{
    std::unique_ptr<Simple> mySmartPtr1 = create();
    auto mySmartPtr2 = create();
    std::cout << "ELO\n";
    return 0;
}