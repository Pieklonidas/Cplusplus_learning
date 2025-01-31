#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <set>
#include <map>
#include "HashMap.hpp"

void streamIteratorsExample()
{
    std::vector<int> myVector(10);
    std::iota(begin(myVector), end(myVector), 1);
    std::copy(cbegin(myVector), cend(myVector), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "Enter numbers separated by white space." << std::endl;
    std::cout << "Press Ctrl+Z followed by Enter to stop." << std::endl;
    std::istream_iterator<int> numbersIter(std::cin);
    std::istream_iterator<int> endIter;
    int sum = std::accumulate(numbersIter, endIter, 0);
    std::cout << "Sum: " << sum << std::endl;
}

class MoveableClass
{
    public:
        MoveableClass() {
            std::cout << "Default constructor" << std::endl;
        }
        MoveableClass(const MoveableClass& src) {
            std::cout << "Copy constructor" << std::endl;
        }
        MoveableClass(MoveableClass&& src) noexcept {
            std::cout << "Move constructor" << std::endl;
        }
        MoveableClass& operator=(const MoveableClass& rhs) {
            std::cout << "Copy assignment operator" << std::endl;
            return *this;
        }
        MoveableClass& operator=(MoveableClass&& rhs) noexcept {
            std::cout << "Move assignment operator" << std::endl;
            return *this;
        }
};

void iteratorAdaptorsExample()
{
    std::vector<int> myVector { 1, 1, 2, 3, 4, 3, 7, 1, 2, 5, 4, 3, 7 };
    int num;
    std::cout << "Enter a number to find: ";
    std::cin >> num;

    auto it1 = std::find(begin(myVector), end(myVector), num);
    auto it2 = std::find(rbegin(myVector), rend(myVector), num);
    
    if(it1 != end(myVector))
    {
        std::cout << "Found " << num << " at position " << it1 - begin(myVector)
                  << " going forward." << std::endl;
        std::cout << "Found " << num << " at position "
                  << it2.base() - 1 - begin(myVector) << " going backward." << std::endl;
    }
    else
    {
        std::cout << "Failed to find " << num << std::endl;
    }

    std::vector<int> vectorOne { 101, 202, 100, 303, 404, 100 };
    std::vector<int> vectorTwo;
    std::back_insert_iterator<std::vector<int>> inserter(vectorTwo);
    std::copy_if(cbegin(vectorOne), cend(vectorOne), inserter,
                 [](int i){ return i != 100; });
    std::copy(cbegin(vectorTwo), cend(vectorTwo), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;

    std::copy_if(cbegin(vectorOne), cend(vectorOne), std::back_inserter(vectorTwo),
                 [](int i){ return i > 300; });
    std::copy(cbegin(vectorTwo), cend(vectorTwo), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;

    std::set<int> setOne;

    std::insert_iterator<std::set<int>> inserter2(setOne, begin(setOne));
    std::copy_if(cbegin(vectorOne), cend(vectorOne), inserter2,
                 [](int i){ return i != 100; });
    std::copy(cbegin(setOne), cend(setOne), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;

    std::vector<MoveableClass> vecSource;
    MoveableClass mc;
    vecSource.push_back(mc);
    vecSource.push_back(mc);

    std::vector<MoveableClass> vecOne(cbegin(vecSource), cend(vecSource));

    std::vector<MoveableClass> vecTwo(make_move_iterator(begin(vecSource)), make_move_iterator(end(vecSource)));
}

template<typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator find_all(InputIterator first, InputIterator last, OutputIterator dest, Predicate pred)
{
    while (first != last)
    {
        if(pred(*first))
        {
            *dest = first;
            ++dest;
        }
        ++first;
    }
    return dest;
}

void findAllExample()
{
    std::vector<int> vec{ 3, 4, 5, 4, 5, 6, 5, 8 };
    std::vector<std::vector<int>::iterator> matches;

    find_all(begin(vec), end(vec), std::back_inserter(matches),
             [](int i){ return i == 5; });
    
    std::cout << "Found " << matches.size() << " matching elements: " << std::endl;
    for(const auto& it : matches)
    {
        std::cout << *it << " at position " << (it - cbegin(vec)) << std::endl;
    }
}

template <typename IteratorType>
void iteratorTraitsTest(IteratorType it)
{
    typename std::iterator_traits<IteratorType>::value_type temp;
    temp = *it;
    std::cout << temp << std::endl;
}

void iteratorTraitsExample()
{
    std::vector<int> v{5};
    iteratorTraitsTest(begin(v));
}

void hashMapExample()
{
    ProCpp::hash_map<int, int> myHash;
    myHash.insert(std::make_pair(4, 40));
    myHash.insert(std::make_pair(6, 60));

    auto x = myHash.find(4);
    if(x != nullptr)
    {
        std::cout << "4 maps to " << x->second << std::endl;
    }
    else
    {
        std::cout << "cannot find 4 in map" << std::endl;
    }

    myHash.erase(4);
    auto x2 = myHash.find(4);
    if(x2 != nullptr)
    {
        std::cout << "4 maps to " << x2->second << std::endl;
    }
    else
    {
        std::cout << "cannot find 4 in map" << std::endl;
    }

    myHash[4] = 35;
    myHash[4] = 64;

    auto x3 = myHash.find(4);
    if(x3 != nullptr)
    {
        std::cout << "4 maps to " << x3->second << std::endl;
    }
    else
    {
        std::cout << "cannot find 4 in map" << std::endl;
    }

    ProCpp::hash_map<int, int> other(std::equal_to<>(), 11);
    ProCpp::swap(other, myHash);
    auto x4 = other.find(4);
    if(x4 != nullptr)
    {
        std::cout << "4 maps to " << x4->second << std::endl;
    }
    else
    {
        std::cout << "cannot find 4 in map" << std::endl;
    }

    ProCpp::hash_map<int, int> myHash2(other);
    ProCpp::hash_map<int, int> myHash3;
    myHash3 = myHash2;

    auto x5 = myHash3.find(4);
    if(x5 != nullptr)
    {
        std::cout << "4 maps to " << x5->second << std::endl;
    }
    else
    {
        std::cout << "cannot find 4 in map" << std::endl;
    }

    ProCpp::hash_map<int, int> myHash4(std::move(myHash3));
    ProCpp::hash_map<int, int> myHash5;
    myHash5 = std::move(myHash4);

    auto x6 = myHash5.find(4);
    if(x6 != nullptr)
    {
        std::cout << "4 maps to " << x6->second << std::endl;
    }
    else
    {
        std::cout << "cannot find 4 in map" << std::endl;
    }
}

void hashMapIteratorExample()
{
    ProCpp::hash_map<std::string, int> myHash;
    myHash.insert(std::make_pair("KeyOne", 100));
    myHash.insert(std::make_pair("KeyTwo", 200));
    myHash.insert(std::make_pair("KeyThree", 300));

    for (auto it = myHash.cbegin(); it != myHash.cend(); ++it) {
        std::cout << it->first << " maps to " << (*it).second << std::endl;
    }

    for (auto& p : myHash) {
        std::cout << p.first << " maps to " << p.second << std::endl;
    }

    for (auto&[key, value] : myHash) {
        std::cout << key << " maps to " << value << std::endl;
    }

    std::map<std::string, int> myMap(cbegin(myHash), cend(myHash));
    for (auto& p : myMap) {
        std::cout << p.first << " maps to " << p.second << std::endl;
    }
}

int main()
{  
    // streamIteratorsExample();
    // iteratorAdaptorsExample();
    // findAllExample();
    // iteratorTraitsExample();
    // hashMapExample();
    hashMapIteratorExample();
    return 0;
}