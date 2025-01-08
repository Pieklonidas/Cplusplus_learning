#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <functional>
#include <string>
#include <string_view>
#include <list>
#include <map>
#include <utility>

bool perfectScore(int num)
{
    return (num >= 100);
}

void findExample()
{
    int num;
    std::vector<int> myVector;
    while(true)
    {
        std::cout << "Enter a number to add (0 to stop): ";
        std::cin >> num;
        if(num == 0)
        {
            break;
        }
        myVector.push_back(num);
    }

    {
        auto endIt = cend(myVector);
        auto it = find_if(cbegin(myVector), endIt, perfectScore); // ADL
        if (it == endIt)
        {
            std::cout << "No perfect scores" << std::endl;
        }
        else
        {
            std::cout << "Found a perfect score of " << *it << std::endl;
        }
    }

    {
        double sum = std::accumulate(cbegin(myVector), cend(myVector), 0.0);
        std::cout << "The arithmetic mean is: " << sum / myVector.size() << std::endl;
        double mult = std::accumulate(cbegin(myVector), cend(myVector), 1.0, std::multiplies<int>());
        std::cout << "The geometric mean is: " << std::pow(mult, 1.0 / myVector.size()) << std::endl;
    }

    while(true)
    {
        std::cout << "Enter a number to lookup (0 to stop): ";
        std::cin >> num;
        if(num == 0)
        {
            break;
        }
        auto endIt = cend(myVector);
        auto it = std::find(cbegin(myVector), endIt, num);
        if(it == endIt)
        {
            std::cout << "Could not find " << num << std::endl;
        }
        else
        {
            std::cout << "Found " << *it << std::endl;
        }
    }
}

void process(const std::vector<int>& vec, std::function<void(int)> f)
{
    for(auto& i : vec)
    {
        f(i);
    }
}

void print(int num)
{
    std::cout << num << " ";
}

void functionExample()
{
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,0};
    process(vec, print);
    std::cout << std::endl;
    
    int sum = 0;
    process(vec, [&sum](int num){ sum += num; });
    std::cout << "Sum = " << sum << std::endl;
}

void lambdaExample()
{
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int value = 3;
    int cntLambdaCalled = 0;
    int cnt = std::count_if(cbegin(vec), cend(vec),
                            [value, &cntLambdaCalled](int i)
                            {
                                ++cntLambdaCalled;
                                return i > value; 
                            });
    std::cout << "The lambda expression was called " << cntLambdaCalled << " times." << std::endl;
    std::cout << "Found " << cnt << " values > " << value << std::endl;

    std::vector<int> vec2(10);
    value = 1;
    std::generate(begin(vec2), end(vec2), [&value]{ value *= 2; return value; });
    for(const auto& i : vec2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void func(int num, std::string_view str)
{
    std::cout << "func(" << num << ", " << str << ")" << std::endl;
}

void increment(int& value) { ++value; }

void bindExample()
{
    std::string myString = "abc";
    auto f1 = std::bind(func, std::placeholders::_1, myString);
    f1(16);

    auto f2 = std::bind(func, std::placeholders::_2, std::placeholders::_1);
    f2("Test", 32);

    int index = 0;
    auto incr = std::bind(increment, index);
    incr();
    std::cout << "Index is: " << index << std::endl;

    auto incr2 = std::bind(increment, std::ref(index));
    incr2();
    std::cout << "Index is: " << index << std::endl;

    std::vector<int> vec{1,2,3,4,5,100,200};
    auto endIter = end(vec);
    auto it = std::find_if(begin(vec), endIter, std::bind(std::greater_equal<>(), std::placeholders::_1, 100));
    if (it == endIter) 
    {
        std::cout << "No perfect scores" << std::endl;
    } 
    else 
    {
        std::cout << "Found a \"perfect\" score of " << *it << std::endl;
    }

    auto endIter2 = end(vec);
    auto it2 = std::find_if(begin(vec), endIter, std::not_fn(perfectScore));
    if (it2 == endIter2) 
    {
        std::cout << "All perfect scores" << std::endl;
    } 
    else 
    {
        std::cout << "Found a \"less-than-perfect\" score of " << *it << std::endl;
    }
}

void searchExample()
{
    std::vector<int> vec{ 5, 6, 9, 8, 8, 3 };
    auto beginIter = cbegin(vec);
    auto endIter = cend(vec);

    auto it = find_if_not(beginIter, endIter, [](int i){ return i < 8; });
    if(it != endIter)
    {
        std::cout << "First element not < 8 i is " << *it << std::endl;
    }

    it = std::adjacent_find(beginIter, endIter);
    if(it != endIter)
    {
        std::cout << "Found two consecutive equal elements with value " << *it << std::endl;
        std::cout << "It's on the position: " << it - beginIter << std::endl;
    }
    std::vector<int> targets = { 8, 9 };
    it = std::find_first_of(beginIter, endIter, cbegin(targets), cend(targets));
    if(it != endIter)
    {
        std::cout << "Found one of 8 or 9: " << *it << std::endl;
        std::cout << "It's on the position: " << it - beginIter << std::endl;
    }

    std::vector<int> sub = { 8, 3 };
    it = std::search(beginIter, endIter, cbegin(sub), cend(sub));
    if(it != endIter)
    {
        std::cout << "Found subsequence {8, 3}" << std::endl;
        std::cout << "It's on the position: " << it - beginIter << std::endl;
    }
    else
    {
        std::cout << "Unable to find subsequence {8,3}" << std::endl;
    }

    it = search_n(beginIter, endIter, 2, 8);
    if(it != endIter)
    {
        std::cout << "Found two consecutive 8s" << std::endl;
        std::cout << "It's on the position: " << it - beginIter << std::endl;
    }
    else
    {
        std::cout << "Unable to find two consecutive 8s" << std::endl;
    }
}

template<typename Container>
void populateContainer(Container& cont)
{
    int num;
    while (true)
    {
        std::cout << "Enter a number (0 to quit): ";
        std::cin >> num;
        if(num == 0)
        {
            break;
        }
        cont.push_back(num);
    }
}

void compareExample()
{
    std::vector<int> myVector;
    std::list<int> myList;

    std::cout << "Populate the vector: " << std::endl;
    populateContainer(myVector);
    std::cout << "Populate the list: " << std::endl;
    populateContainer(myList);

    auto vecBeginIt = cbegin(myVector);
    auto vecEndIt = cend(myVector);
    auto listBeginIt = cbegin(myList);
    auto listEndIt = cend(myList);

    if(std::equal(vecBeginIt, vecEndIt, listBeginIt, listEndIt))
    {
        std::cout << "The two containers have equal elements" << std::endl;
    }
    else
    {
        auto miss = std::mismatch(vecBeginIt, vecEndIt, listBeginIt, listEndIt);
        std::cout << "The following initial elements are the same in "
                  << "the vector and the list:" << std::endl;
        for(auto i = vecBeginIt; i != miss.first; ++i)
        {
            std::cout << *i << '\t';

        }
        std::cout << std::endl;
    }
    if(std::lexicographical_compare(vecBeginIt, vecEndIt, listBeginIt, listEndIt))
    {
        std::cout << "The vector is lexicographically first." << std::endl;
    }
    else
    {
        std::cout << "The list is lexicographically first." << std::endl;
    }
}

void countExample()
{
    std::vector<int> vec2{ 1, 1, 1, 1 };
    if(std::all_of(cbegin(vec2), cend(vec2), [](int i){ return i == 1; }))
    {
        std::cout << "All elements are == 1" << std::endl;
    }
    else
    {
        std::cout << "Not all elements are == 1" << std::endl;
    }

    std::vector<int> vec3{ 0, 0, 1, 0 };
    if(std::any_of(cbegin(vec3), cend(vec3), [](int i){ return i == 1; }))
    {
        std::cout << "At least one element == 1" << std::endl;
    }
    else
    {
        std::cout << "No elements are == 1" << std::endl;
    }

    std::vector<int> vec4{ 0, 0, 0, 0 };
    if(std::none_of(cbegin(vec4), cend(vec4), [](int i){ return i == 1; }))
    {
        std::cout << "All elements are =/= 1" << std::endl;
    }
    else
    {
        std::cout << "Not all elements are =/= 1" << std::endl;
    }
}

template <typename T>
void printContainer(const std::vector<T>& con)
{
    std::cout << "The vector contains:" << std::endl;
    for(const auto& i : con) { std::cout << i << " "; }
    std::cout << std::endl;
}

void transformExample()
{
    std::vector<int> myVector;
    populateContainer(myVector);
    printContainer(myVector);

    std::transform(begin(myVector), end(myVector), begin(myVector), [](int i){ return i+100; });
    printContainer(myVector);

    std::vector<int> vec1, vec2;
    std::cout << "Vector1:" << std::endl; populateContainer(vec1);
    std::cout << "Vector2:" << std::endl; populateContainer(vec2);

    if(vec2.size() < vec1.size())
    {
        std::cout << "Vector2 should be at least the same size as vector1." << std::endl;
        return;
    }
    std::cout << "Vector1 "; printContainer(vec1);
    std::cout << "Vector2 "; printContainer(vec2);

    std::transform(begin(vec1), end(vec1), begin(vec2), begin(vec1), [](int a, int b){ return a+b; });
    std::cout << "Vector1 "; printContainer(vec1);
    std::cout << "Vector2 "; printContainer(vec2);
}

void copyExample()
{
    std::vector<int> vec1, vec2;
    populateContainer(vec1);
    vec2.resize(vec1.size());
    std::copy(cbegin(vec1), cend(vec1), begin(vec2));
    printContainer(vec2);

    std::copy_backward(cbegin(vec1), cend(vec1), end(vec2));
    printContainer(vec2);

    auto endIterator = std::copy_if(cbegin(vec1), cend(vec1), begin(vec2), [](int i){ return i%2 == 0; });
    printContainer(vec2);
    vec2.erase(endIterator, end(vec2));
    printContainer(vec2);

    vec1.clear();
    vec2.clear();
    populateContainer(vec1);
    size_t cnt = 0;
    std::cout << "Enter number of elements you want to copy: ";
    std::cin >> cnt;
    cnt = std::min(cnt, size(vec1));
    vec2.resize(cnt);
    std::copy_n(cbegin(vec1), cnt, begin(vec2));
    printContainer(vec2);
}

void replaceExample()
{
    std::vector<int> vec { 1, 2, 3, 4, 5 };
    std::replace_if(begin(vec), end(vec), [](int i){ return i % 2 != 0; }, 0);
    printContainer(vec);
}

void removeExample()
{
    std::vector<std::string> myVector{"", "one", "", "two", "three", "four"};
    printContainer(myVector);
    
    auto it = remove_if(begin(myVector), end(myVector), [](const std::string& str){ return str.empty(); });
    myVector.erase(it, end(myVector));

    printContainer(myVector);
}

void forEachExample()
{
    std::map<int, int> myMap = { {4, 40}, {5, 50}, {6, 60} };
    std::for_each(cbegin(myMap), cend(myMap), [](const auto& p){ std::cout << p.first << "->" << p.second << std::endl; } );

    std::vector<int> myVector;
    populateContainer(myVector);

    int sum = 0;
    int product = 1;
    std::for_each(cbegin(myVector), cend(myVector), [&sum, &product](int i){ sum += i; product *= i; });
    std::cout << "The sum is " << sum << std::endl;
    std::cout << "The product is " << product << std::endl;
}

void swapAndExchangeExample()
{
    int a = 11;
    int b = 22;
    std::cout << "Before swap(): a = " << a << ", b = " << b << std::endl;
    std::swap(a,b);
    std::cout << "After swap(): a = " << a << ", b = " << b << std::endl;

    a = 11;
    b = 22;
    std::cout << "Before exchange(): a = " << a << ", b = " << b << std::endl;
    int returnedValue = std::exchange(a,b);
    std::cout << "After exchange(): a = " << a << ", b = " << b << std::endl;
    std::cout << "exchange() returned: " << returnedValue << std::endl;
}

void partitionExample()
{
    std::vector<int> vec1, vecOdd, vecEven;
    populateContainer(vec1);
    vecOdd.resize(size(vec1)); vecEven.resize(size(vec1));
    auto pairIters = std::partition_copy(cbegin(vec1), cend(vec1), begin(vecEven), begin(vecOdd), [](int i){ return i%2 == 0; });
    vecEven.erase(pairIters.first, end(vecEven));
    vecOdd.erase(pairIters.second, end(vecOdd));

    std::cout << "Even numbers: ";
    printContainer(vecEven);
    std::cout << "Odd numbers: ";
    printContainer(vecOdd);

    std::vector<int> vec;
    populateContainer(vec);
    std::partition(begin(vec), end(vec), [](int i){ return i%2 == 0; });
    std::cout << "Partitioned result: ";
    printContainer(vec);
}

void binarySearchExample()
{
    std::vector<int> vec;
    populateContainer(vec);
    std::sort(begin(vec), end(vec));
    std::cout << "Sorted vector: ";
    printContainer(vec);
    while (true)
    {
        int num;
        std::cout << "Enter a number to insert (0 to quit): ";
        std::cin >> num;
        if (num == 0)
        {
            break;
        }

        auto iter = std::lower_bound(begin(vec), end(vec), num);
        vec.insert(iter, num);

        std::cout << "New vector: ";
        printContainer(vec);
    }
    
    while (true)
    {
        int num;
        std::cout << "Enter a number to find (0 to quit): ";
        std::cin >> num;
        if (num == 0)
        {
            break;
        }
        if(std::binary_search(cbegin(vec), cend(vec), num))
        {
            std::cout << "That number is in the vector." << std::endl;
        }
        else
        {
            std::cout << "That number is not in the vector." << std::endl;
        }
    }
}

template<typename Iterator>
void DumpRange(std::string_view message, Iterator begin, Iterator end)
{
    std::cout << message;
    for_each(begin, end, [](const auto& element) { std::cout << element << " "; });
    std::cout << std::endl;
}

void setAlgorithmsExample()
{
    std::vector<int> vec1, vec2, result;
    std::cout << "Enter elements for set 1:" << std::endl;
    populateContainer(vec1);
    std::cout << "Enter elements for set 2:" << std::endl;
    populateContainer(vec2);

    std::sort(begin(vec1), end(vec1));
    std::sort(begin(vec2), end(vec2));

    DumpRange("Set 1: ", cbegin(vec1), cend(vec1));
    DumpRange("Set 2: ", cbegin(vec2), cend(vec2));

    if(std::includes(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2)))
    {
        std::cout << "The second set is a subset of the first." << std::endl;
    }
    if(std::includes(cbegin(vec2), cend(vec2), cbegin(vec1), cend(vec1)))
    {
        std::cout << "The first set is a subset of the second." << std::endl;
    }

    result.resize(size(vec1) + size(vec2));
    auto newEnd = std::set_union(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2), begin(result));
    DumpRange("The union is: ", begin(result), newEnd);
    
    newEnd = std::set_intersection(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2), begin(result));
    DumpRange("The intersection is: ", begin(result), newEnd);

    newEnd = std::set_difference(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2), begin(result));
    DumpRange("The difference is: ", begin(result), newEnd);

    newEnd = std::set_symmetric_difference(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2), begin(result));
    DumpRange("The symmetric difference is: ", begin(result), newEnd);

    std::merge(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2), begin(result));

    DumpRange("Merged vector: ", cbegin(result), cend(result));
}

int main()
{
    // findExample();
    // functionExample();
    // lambdaExample();
    // bindExample();
    // searchExample();
    // compareExample();
    // countExample();
    // transformExample();
    // copyExample();
    // replaceExample();
    // removeExample();
    // forEachExample();
    // swapAndExchangeExample();
    // partitionExample();
    // binarySearchExample();
    setAlgorithmsExample();
    return 0;
}