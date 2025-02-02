#pragma once
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm>
#include "HashMapIterator.hpp"

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
    using hasher = Hash;
    using key_equal = KeyEqual;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using hash_map_type = hash_map<Key, T, KeyEqual, Hash>;

    using iterator = hash_map_iterator<hash_map_type>;
    using const_iterator = const_hash_map_iterator<hash_map_type>;

private:
    using ListType = std::list<value_type>;

public:
    using local_iterator = typename ListType::iterator;
    using const_local_iterator = typename ListType::const_iterator;

    virtual ~hash_map() = default;

    explicit hash_map(const KeyEqual& equal = KeyEqual(), size_t numBuckets = 101, const Hash& hash = Hash());

    template <typename InputIterator>
    hash_map(InputIterator first, InputIterator last, const KeyEqual& equal = KeyEqual(), size_t numBuckets = 101, const Hash& hash = Hash());

    explicit hash_map(std::initializer_list<value_type> il, const KeyEqual& equal = KeyEqual(), size_t numBuckets = 101, const Hash& hash = Hash());

    hash_map(const hash_map<Key, T, KeyEqual, Hash>& src) = default;
    hash_map(hash_map<Key, T, KeyEqual, Hash>&& src) noexcept = default;

    hash_map<Key, T, KeyEqual, Hash>& operator=(const hash_map<Key, T, KeyEqual, Hash>& rhs);
    hash_map<Key, T, KeyEqual, Hash>& operator=(hash_map<Key, T, KeyEqual, Hash>&& rhs) noexcept;
    hash_map<Key, T, KeyEqual, Hash>& operator=(std::initializer_list<value_type> il);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    T& operator[](const key_type& k);
    std::pair<iterator, bool> insert(const value_type& x);
    iterator insert(const_iterator hint, const value_type& x);
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last);
    void insert(std::initializer_list<value_type> il);

    size_type erase(const key_type& k);
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);

    void swap(hash_map<Key, T, KeyEqual, Hash>& other) noexcept;
    void clear() noexcept;

    key_equal key_eq() const;
    hasher hash_function() const;

    iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;
    std::pair<iterator, iterator> equal_range(const key_type& k);
    std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

    size_type count(const key_type& k) const;

    friend class hash_map_iterator<hash_map_type>;
    friend class const_hash_map_iterator<hash_map_type>;

private:
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

    auto iter = std::find_if(std::begin(mBuckets[bucket]), std::end(mBuckets[bucket]),
         [this, &k](const auto& element){ return mEqual(element.first, k); });
    
    return std::make_pair(iter, bucket);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::iterator 
    hash_map<Key, T, KeyEqual, Hash>::find(const key_type& k)
{
    auto [it, bucket] = findElement(k);
    if(it == std::end(mBuckets[bucket]))
    {
        return end();
    }

    return hash_map_iterator<hash_map_type>(bucket, it, this);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::const_iterator 
    hash_map<Key, T, KeyEqual, Hash>::find(const key_type& k) const
{
    return const_cast<hash_map_type*>(this)->find(k);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
std::pair<typename hash_map<Key, T, KeyEqual, Hash>::iterator, typename hash_map<Key, T, KeyEqual, Hash>::iterator> 
    hash_map<Key, T, KeyEqual, Hash>::equal_range(const key_type& k)
{
    auto it = find(k);
    return std::make_pair(it, it);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
std::pair<typename hash_map<Key, T, KeyEqual, Hash>::const_iterator, typename hash_map<Key, T, KeyEqual, Hash>::const_iterator> 
    hash_map<Key, T, KeyEqual, Hash>::equal_range(const key_type& k) const
{
    const_iterator it = find(k);
    return std::make_pair(it, it);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::size_type 
    hash_map<Key, T, KeyEqual, Hash>::count(const key_type& k) const
{
    if(find(k) == end())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
T& hash_map<Key, T, KeyEqual, Hash>::operator[](const key_type& k)
{
    return ((insert(std::make_pair(k, T()))).first)->second;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
std::pair<typename hash_map<Key, T, KeyEqual, Hash>::iterator, bool> hash_map<Key, T, KeyEqual, Hash>::insert(const value_type& x)
{
    auto [it, bucket] = findElement(x.first);
    bool inserted = false;
    if(it == std::end(mBuckets[bucket]))
    {
        it = mBuckets[bucket].insert(it, x);
        inserted = true;
        mSize++;
    }
    return std::make_pair(hash_map_iterator<hash_map_type>(bucket, it, this), inserted);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::iterator hash_map<Key, T, KeyEqual, Hash>::insert(const_iterator, const value_type& x)
{
    return insert(x).first;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
template<typename InputIterator>
void hash_map<Key, T, KeyEqual, Hash>::insert(InputIterator first, InputIterator last)
{
    std::insert_iterator<hash_map_type> inserter(*this, begin());
    std::copy(first, last, inserter);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::insert(std::initializer_list<value_type> il)
{
    insert(std::begin(il), std::end(il));
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::size_type hash_map<Key, T, KeyEqual, Hash>::erase(const key_type& k)
{
    auto [it, bucket] = findElement(k);
    if(it != std::end(mBuckets[bucket]))
    {
        mBuckets[bucket].erase(it);
        mSize--;
        return 1;
    }
    else
    {
        return 0;
    }
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::iterator hash_map<Key, T, KeyEqual, Hash>::erase(iterator position)
{
    iterator next = position;
    ++next;
    mBuckets[position.mBucketIndex].erase(position.mListIterator);
    mSize--;
    return next;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::iterator hash_map<Key, T, KeyEqual, Hash>::erase(iterator first, iterator last)
{
    for(iterator next = first; next != last;)
    {
        next = erase(next);
    }
    return last;
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

template<typename Key, typename T, typename KeyEqual, typename Hash>
bool hash_map<Key, T, KeyEqual, Hash>::empty() const
{
    return mSize == 0;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::size_type hash_map<Key, T, KeyEqual, Hash>::size() const
{
    return mSize;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::size_type hash_map<Key, T, KeyEqual, Hash>::max_size() const
{
    return mBuckets[0].max_size();
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::iterator hash_map<Key, T, KeyEqual, Hash>::begin()
{
    if(mSize == 0)
    {
        return end();
    }
    for(size_t i = 0; i < mBuckets.size(); ++i)
    {
        if(!mBuckets[i].empty())
        {
            return hash_map_iterator<hash_map_type>(i, std::begin(mBuckets[i]), this);
        }
    }
    return end();
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::iterator hash_map<Key, T, KeyEqual, Hash>::end()
{
    size_t bucket = mBuckets.size()-1;
    return hash_map_iterator<hash_map_type>(bucket, std::end(mBuckets[bucket]), this);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::const_iterator hash_map<Key, T, KeyEqual, Hash>::begin() const
{
    return const_cast<hash_map_type*>(this)->begin();
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::const_iterator hash_map<Key, T, KeyEqual, Hash>::end() const
{
    return const_cast<hash_map_type*>(this)->end();
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::const_iterator hash_map<Key, T, KeyEqual, Hash>::cbegin() const
{
    return begin();
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::const_iterator hash_map<Key, T, KeyEqual, Hash>::cend() const
{
    return end();
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
template<typename InputIterator>
hash_map<Key, T, KeyEqual, Hash>::hash_map(InputIterator first, InputIterator last,
                                           const KeyEqual& equal, size_type numBuckets, const Hash& hash)
                                           : hash_map(equal, numBuckets, hash)
{
    insert(first, last);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
hash_map<Key, T, KeyEqual, Hash>::hash_map(std::initializer_list<value_type> il,
                                           const KeyEqual& equal, size_type numBuckets, const Hash& hash)
                                           : hash_map(equal, numBuckets, hash)
{
    insert(std::begin(il), std::end(il));
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
hash_map<Key, T, KeyEqual, Hash>& hash_map<Key, T, KeyEqual, Hash>::operator=(std::initializer_list<value_type> il)
{
    hash_map_type newHashMap(il, mEqual, mBuckets.size(), mHash);
    swap(newHashMap);
    return *this;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::key_equal hash_map<Key, T, KeyEqual, Hash>::key_eq() const
{
    return mEqual;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::hasher hash_map<Key, T, KeyEqual, Hash>::hash_function() const
{
    return mHash;
}

}