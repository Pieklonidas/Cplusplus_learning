#pragma once
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm>

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

    std::pair<typename ListType::iterator, size_t> findElement(const key_type& k);
};

template <typename Key, typename T, typename KeyEqual, typename Hash>
hash_map<Key, T, KeyEqual, Hash>::hash_map(const KeyEqual& equal, size_t numBuckets, const Hash& hash)
    : mBuckets(numBuckets), mEqual(equal), mHash(hash)
{
    if(numBuckets == 0)
    {
        throw std::invalid_argument("Number of buckets must be positive");
    }
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
std::pair<typename hash_map<Key, T, KeyEqual, Hash>::ListType::iterator, size_t>
    hash_map<Key, T, KeyEqual, Hash>::findElement(const key_type& k)
{
    size_t bucket = mHash(k) % mBuckets.size();

    auto iter = std::find_if(begin(mBuckets[bucket]), end(mBuckets[bucket]),
         [this, &k](const auto& element){ return mEqual(element.first, k); });
    
    return std::make_pair(iter, bucket);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::value_type* 
    hash_map<Key, T, KeyEqual, Hash>::find(const key_type& k)
{
    auto [it, bucket] = findElement(k);
    if(it == end(mBuckets[bucket]))
    {
        return nullptr;
    }

    return &(*it);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
const typename hash_map<Key, T, KeyEqual, Hash>::value_type* 
    hash_map<Key, T, KeyEqual, Hash>::find(const key_type& k) const
{
    return const_cast<hash_map<Key, T, KeyEqual, Hash>*>(this)->find(k);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
T& hash_map<Key, T, KeyEqual, Hash>::operator[](const key_type& k)
{
    auto [it, bucket] = findElement(k);
    if(it == end(mBuckets[bucket]))
    {
        mSize++;
        mBuckets[bucket].push_back(std::make_pair(k, T()));
        return mBuckets[bucket].back().second;
    }
    else
    {
        return it->second;
    }
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::insert(const value_type& x)
{
    auto [it, bucket] = findElement(x.first);
    if(it != end(mBuckets[bucket]))
    {
        return;
    }
    else
    {
        mSize++;
        mBuckets[bucket].push_back(x);
    }
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::erase(const key_type& k)
{
    auto [it, bucket] = findElement(k);
    if(it != end(mBuckets[bucket]))
    {
        mBuckets[bucket].erase(it);
        mSize--;
    }
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::clear() noexcept
{
    for(auto& bucket : mBuckets)
    {
        bucket.clear();
    }
    mSize = 0;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::swap(hash_map<Key, T, KeyEqual, Hash>& other) noexcept
{
    using std::swap;

    swap(mBuckets, other.mBuckets);
    swap(mSize, other.mSize);
    swap(mEqual, other.mEqual);
    swap(mHash, other.mHash);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
void swap(hash_map<Key, T, KeyEqual, Hash>& first, hash_map<Key, T, KeyEqual, Hash>& second) noexcept
{
    first.swap(second);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
hash_map<Key, T, KeyEqual, Hash>& 
    hash_map<Key, T, KeyEqual, Hash>::operator=(const hash_map<Key, T, KeyEqual, Hash>& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }

    auto copy = rhs;
    swap(copy);
    return *this;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
hash_map<Key, T, KeyEqual, Hash>& 
    hash_map<Key, T, KeyEqual, Hash>::operator=(hash_map<Key, T, KeyEqual, Hash>&& rhs) noexcept
{
    swap(rhs);
    return *this;
}
}


