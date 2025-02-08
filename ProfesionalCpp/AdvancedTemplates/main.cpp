#include <iostream>
#include <vector>
#include <deque>
#include <string_view>
#include <string>
#include <tuple>
#include <utility>
#include <type_traits>
#include "PartialSpecializationPointerClass.hpp"
#include "MixinClasses.hpp"
#include "Factorial.hpp"
#include "Loop.hpp"
#include "TuplePrint.hpp"

template<typename T,
    template <typename E, typename Allocator = std::allocator<E>> class Container = std::vector>
Container<T> makeAContainer(T a, T b, T step)
{
    Container<T> temp;
    for(T start = a; start <= b; start+=step)
    {
        temp.push_back(start);
    }
    return temp;
}

void templateTemplateParamterExample()
{
    auto container = makeAContainer<int, std::vector>(0, 10, 2);
    for(const auto elem : container)
    {
        std::cout << elem << std::endl;
    }

    auto container2 = makeAContainer<int, std::deque>(10, 16, 2);
    for(const auto elem : container2)
    {
        std::cout << elem << std::endl;
    }
}

class ObjectA
{
public:
    int x = 1;
    int y = 2;
};

template <typename T, const T DEFAULT>
void coutAddedValue(T val)
{
    std::cout << val + DEFAULT << std::endl;
}

template <typename T, const T& DEFAULT>
void coutObject(T val)
{
    std::cout << val.x + DEFAULT.x << " " << val.y + DEFAULT.x << std::endl;
}

namespace 
{
    ObjectA A{5, 7};
}

void nonTypeParamterExample()
{
    coutAddedValue<int, 7>(7);
    coutAddedValue<char, char(5)>('a');
    ObjectA B{5, 7};
    coutObject<ObjectA, A>(B);
}

void partialSpecializationExample()
{
    int x = 1;
    PointerClass A(x);
    std::cout << A.getX() << std::endl;
    {
        PointerClass B(&x);
        std::cout << B.getX() << std::endl;
        std::cout << *B.getX() << std::endl;
        A.setX(5);
        std::cout << A.getX() << std::endl;
        std::cout << *B.getX() << std::endl;
        std::cout << "Just x: " << x << std::endl;
        B.setX(10);
        std::cout << A.getX() << std::endl;
        std::cout << *B.getX() << std::endl;
        std::cout << "Just x: " << x << std::endl;
    }
    std::cout << "Still x: " << x << std::endl;
}

void handleValue(int value) { std::cout << "Integer: " << value << std::endl; }
void handleValue(double value) { std::cout << "Double: " << value << std::endl; }
void handleValue(std::string_view value) { std::cout << "String: " << value << std::endl; }

void processValues() {};

template <typename T1, typename... Tn>
void processValues(T1&& arg1, Tn&&... args)
{
    handleValue(std::forward<T1>(arg1));
    processValues(std::forward<Tn>(args)...);
}

void variadicTemplateFunctionExample()
{
    processValues(1, 2, 3.56, "test", 1.1f);
}

void mixinClassesExample()
{
    MyClass<Mixin1, Mixin2> a(Mixin1(11), Mixin2(22));
    a.Mixin1Func();
    a.Mixin2Func();

    MyClass<Mixin1> b(Mixin1(33));
    b.Mixin1Func();

    MyClass<> c;
}

template <typename... Tn>
void processValues2(const Tn&... args)
{
    (handleValue(args), ...);
}

template <typename... Values>
void printValues(const Values&... values)
{
    ((std::cout << values << std::endl), ...);
}

template <typename T, typename... Values>
double sumValues(const T& init, const Values&... values)
{
    return (init + ... + values);
}

void foldingExpressionsExample()
{
    processValues2(1, "test", 2.34);
    printValues(1, "test", 2.34);
    std::cout << sumValues(4.34) << std::endl;
    std::cout << sumValues(2.34, 2.12, 5.34, 10.17) << std::endl;
}

constexpr unsigned long long factorial(unsigned char f)
{
    if(f==0)
    {
        return 1;
    }
    else
    {
        return f*factorial(f-1);
    }
}

void DoWork(int i)
{
    std::cout << "DoWork(" << i << ")" << std::endl;
}

void DoWork2(std::string str, int i)
{
    std::cout << "DoWork2(" << str << ", " << i << ")" << std::endl;
}

void metaprogrammingExample()
{
    std::cout << Factorial<6>::val << std::endl; // compile time
    constexpr auto f1 = factorial(6); // compile time
    std::cout << f1 << std::endl;
    Loop<3>::Do(DoWork);
    Loop<2>::Do([](int i) { DoWork2("TestStr", i); });
    using MyTuple = std::tuple<int, std::string, bool>;
    MyTuple t1(16, "Test", true);
    tuple_print<MyTuple, std::tuple_size<MyTuple>::value> tp(t1);
    MyTuple t2(78, "ELO", false);
    tuple_print2(t2);
}

template <typename T>
void process_helper(const T& t, std::true_type)
{
    std::cout << t << " is an integral type." << std::endl;
}

template <typename T>
void process_helper(const T& t, std::false_type)
{
    std::cout << t << " is a non-integral type." << std::endl;
}

template <typename T>
void process(const T& t)
{
    process_helper(t, typename std::is_integral<T>::type());
}

template <typename T>
void process2(const T& t)
{
    if constexpr (std::is_integral_v<T>)
    {
        std::cout << t << " is an integral type." << std::endl;
    }
    else
    {
        std::cout << t << " is a non-integral type." << std::endl;
    }
}

template <typename T1, typename T2>
void same(const T1& t1, const T2& t2)
{
    bool areTypesTheSame = std::is_same_v<T1, T2>;
    std::cout << "'" << t1 << "' and '" << t2 << "' are ";
    std::cout << (areTypesTheSame ? "the same types." : "different types.") << std::endl;
}

template <typename T1, typename T2>
std::enable_if_t<std::is_same_v<T1, T2>, bool>
    check_type(const T1& t1, const T2& t2)
{
    std::cout << "'" << t1 << "' and '" << t2 << "' ";
    std::cout << "are the same types." << std::endl;
    return true;
}

template <typename T1, typename T2>
std::enable_if_t<!std::is_same_v<T1, T2>, bool>
    check_type(const T1& t1, const T2& t2)
{
    std::cout << "'" << t1 << "' and '" << t2 << "' ";
    std::cout << "are different types." << std::endl;
    return false;
}

void typeTraitsExample()
{
    if(std::is_integral<int>::value)
    {
        std::cout << "int is integral" << std::endl;
    }
    else
    {
        std::cout << "int is not integral" << std::endl;
    }

    if(std::is_class<int>::value)
    {
        std::cout << "int is a class" << std::endl;
    }
    else
    {
        std::cout << "int is not a class" << std::endl;
    }

    if(std::is_class_v<std::string>)
    {
        std::cout << "string is a class" << std::endl;
    }
    else
    {
        std::cout << "string is not a class" << std::endl;
    }

    process(132);
    process(2.9);
    process("Test");

    process2(162);
    process2(12.9);
    process2("Test2");

    same(1, 32);
    same(1, 3.01);
    same(3.01, "Test");

    check_type(1, 32);
    check_type(1, 3.01);
    check_type("TestCheck", 32.1);
}

int main()
{
    // templateTemplateParamterExample();
    // nonTypeParamterExample();
    // partialSpecializationExample();
    // variadicTemplateFunctionExample();
    // mixinClassesExample();
    // foldingExpressionsExample();
    // metaprogrammingExample();
    typeTraitsExample();
    return 0;
}