#pragma once
#include <string>
#include <vector>
#include <list>

namespace ProCpp
{

template <typename T>
class hash
{
public:
    size_t operator()(const T& key) const;
};

template <typename T>
size_t hash<T>::operator()(const T& key) const
{
    const size_t bytes = sizeof(key);
    size_t sum = 0;
    for(size_t i = 0; i < bytes; i++)
    {
        unsigned char b = *(reinterpret_cast<const unsigned char*>(&key) + i);
        sum += b;
    }
    return sum;
}

template <>
class hash<std::string>
{
public:
    size_t operator()(const std::string& key) const;
};

size_t hash<std::string>::operator()(const std::string& key) const
{
    size_t sum = 0;
    for(auto c : key)
    {
        sum += static_cast<unsigned char>(c);
    }
    return sum;
}

template <typename Key, typename T, typename KeyEqual = std::equal_to<>, typename Hash = hash<Key>>
class hash_map
{
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;

    virtual ~hash_map() = default;

    explicit hash_map(const KeyEqual& equal = KeyEqual(), size_t numBuckets = 101, const Hash& hash = Hash());

    hash_map(const hash_map<Key, T, KeyEqual, Hash>& src) = default;
    hash_map(hash_map<Key, T, KeyEqual, Hash>&& src) noexcept = default;

    hash_map<Key, T, KeyEqual, Hash>& operator=(const hash_map<Key, T, KeyEqual, Hash>& rhs);
    hash_map<Key, T, KeyEqual, Hash>& operator=(hash_map<Key, T, KeyEqual, Hash>&& rhs) noexcept;

    void insert(const value_type& x);
    void erase(const key_type& k);

    void clear() noexcept;

    value_type* find(const key_type& k);
    const value_type* find(const key_type& k) const;

    T& operator[](const key_type& k);

    void swap(hash_map<Key, T, KeyEqual, Hash>& other) noexcept;

private:
    using ListType = std::list<value_type>;
    std::vector<ListType> mBuckets;
    size_t mSize = 0;
    KeyEqual mEqual;
    Hash mHash;
};

}


