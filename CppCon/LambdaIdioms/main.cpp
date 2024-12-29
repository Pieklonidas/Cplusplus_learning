#include <iostream>
#include <memory>
#include <cassert>
#include <variant>

struct X
{
    X()
    {
        static auto _ = []{ std::cout << "called once!\n"; return 0; }();
    }
};

void calledOnceExample()
{
    X x1;
    X x2;
    X x3;
}

void legacyCall(int(*f)(int))
{
    std::cout << f(7) << std::endl;
}

struct Widget {};

template <typename... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};


int main()
{
    calledOnceExample();
    legacyCall([](auto i){ return i*i; });
    auto f = [](auto&&... args) { (std::cout << ... << args); };
    f(42, " HELLO ", 1.5);
    std::cout << std::endl;
    auto twice = [](auto&& f)
    {
        return [=]{ f(); f(); };
    };
    auto print_hihi = twice([]{ std::cout << "hi"; });
    print_hihi();
    std::cout << std::endl;

    auto ptr = std::make_unique<Widget>();
    auto f2 = [ptr=std::move(ptr)]
    {
        std::cout << ptr.get() << '\n';
    };

    assert(ptr == nullptr);
    f2();

    overload f3 = 
    {
        [](int i){ std::cout << "int thingy\n";},
        [](float f){ std::cout << "float thingy\n"; }
    };

    std::variant<int, float> v = 42;
    std::visit(f3, v);
    return 0;
}