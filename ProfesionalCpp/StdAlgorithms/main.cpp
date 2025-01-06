#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <functional>
#include <string>
#include <string_view>
#include <list>

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

int main()
{
    // findExample();
    // functionExample();
    // lambdaExample();
    // bindExample();
    // searchExample();
    // compareExample();
    countExample();
    return 0;
}