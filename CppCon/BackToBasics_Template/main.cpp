#include <iostream>
#include <vector>
#include <set>

template<typename T>
concept SupportLessThan = requires (T x) { x < x; };

template<typename T>
requires std::copyable<T> && SupportLessThan<T>
T mymax(T a, T b)
{
    return b < a ? a : b;
}

template<typename T1, typename T2>
auto mymax2(T1 a, T2 b)
{
    return b < a ? a : b;
}

void printColl(const auto& coll)
{
    for(const auto& elem : coll)
    {
        std::cout << elem << " ";
    }
    std::cout << '\n';
}

template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << firstArg << ' ';
    if constexpr(sizeof...(args) > 0)
    {
        print(args...);
    }
}

template<typename Coll>
concept HasPushBack = requires (Coll c, Coll::value_type v) { c.push_back(v); };

void add(HasPushBack auto& coll, const auto& val)
{
    coll.push_back(val);
}

void add(auto& coll, const auto& val)
{
    coll.insert(val);
}

int main()
{
    std::cout << mymax(1,5) << std::endl;
    std::cout << mymax(1.5, 3.3) << std::endl;
    std::cout << mymax<double>(4, 3.3) << std::endl;
    std::cout << mymax2(2, 3.3) << std::endl;

    std::vector<int> v{1,2,3,4,5};
    std::set<int> s{5,3,2,1,4};

    printColl(v); printColl(s);

    print("abc", 1, 2.3, 'a');

    std::cout << '\n';

    add(v, 7);
    add(s, 7);
    printColl(v); printColl(s);

    return 0;
}