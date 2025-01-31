#pragma once
#include <cstddef>

template <typename HashMap>
class const_hash_map_iterator
{
public:
    using value_type = typename HashMap::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type*;
    using reference = value_type&;
    using list_iterator_type = typename HashMap::ListType::const_iterator;

    const_hash_map_iterator() = default;

    const_hash_map_iterator(size_t bucket, list_iterator_type listIt, const HashMap* hashmap);

    const value_type& operator*() const;

    const value_type* operator->() const;

    const_hash_map_iterator<HashMap>& operator++();
    const_hash_map_iterator<HashMap> operator++(int);

    const_hash_map_iterator<HashMap>& operator--();
    const_hash_map_iterator<HashMap> operator--(int);

    bool operator==(const const_hash_map_iterator<HashMap>& rhs) const;
    bool operator!=(const const_hash_map_iterator<HashMap>& rhs) const;

protected:
    size_t mBucketIndex = 0;
    list_iterator_type mListIterator;
    const HashMap* mHashmap = nullptr;

    void increment();
    void decrement();
};

template <typename HashMap>
const_hash_map_iterator<HashMap>::const_hash_map_iterator(size_t bucket, list_iterator_type listIt, const HashMap* hashmap)
    : mBucketIndex(bucket), mListIterator(listIt), mHashmap(hashmap)
{
}

template <typename HashMap>
const typename const_hash_map_iterator<HashMap>::value_type&
    const_hash_map_iterator<HashMap>::operator*() const
{
    return *mListIterator;
}

template <typename HashMap>
const typename const_hash_map_iterator<HashMap>::value_type*
    const_hash_map_iterator<HashMap>::operator->() const
{
    return &(*mListIterator);
}

template <typename HashMap>
const_hash_map_iterator<HashMap>&
    const_hash_map_iterator<HashMap>::operator++()
{
    increment();
    return *this;
}

template <typename HashMap>
const_hash_map_iterator<HashMap>
    const_hash_map_iterator<HashMap>::operator++(int)
{
    auto oldIt = *this;
    increment();
    return oldIt;
}

template <typename HashMap>
const_hash_map_iterator<HashMap>&
    const_hash_map_iterator<HashMap>::operator--()
{
    decrement();
    return *this;
}

template <typename HashMap>
const_hash_map_iterator<HashMap>
    const_hash_map_iterator<HashMap>::operator--(int)
{
    auto oldIt = *this;
    decrement();
    return oldIt;
}

template <typename HashMap>
void const_hash_map_iterator<HashMap>::increment()
{
    ++mListIterator;

    auto& buckets = mHashmap->mBuckets;
    if(mListIterator == end(buckets[mBucketIndex]))
    {
        for(size_t i = mBucketIndex + 1; i < buckets.size(); i++)
        {
            if(!buckets[i].empty())
            {
                mListIterator = begin(buckets[i]);
                mBucketIndex = i;
                return;
            }
        }
        mBucketIndex = buckets.size() - 1;
        mListIterator = end(buckets[mBucketIndex]);
    }
}

template <typename HashMap>
void const_hash_map_iterator<HashMap>::decrement()
{
    auto& buckets = mHashmap->mBuckets;
    if(mListIterator == begin(buckets[mBucketIndex]))
    {
        for(int i = mBucketIndex - 1; i >= 0; --i)
        {
            if(!buckets[i].empty())
            {
                mListIterator = --end(buckets[i]);
                mBucketIndex = i;
                return;
            }
        }
        mBucketIndex = buckets.size() - 1;
        mListIterator = end(buckets[mBucketIndex]);
    }
    else
    {
        --mListIterator;
    }
}

template <typename HashMap>
bool const_hash_map_iterator<HashMap>::operator==(const const_hash_map_iterator<HashMap>& rhs) const
{
    return (mHashmap == rhs.mHashmap && mBucketIndex == rhs.mBucketIndex && mListIterator == rhs.mListIterator);
}

template <typename HashMap>
bool const_hash_map_iterator<HashMap>::operator!=(const const_hash_map_iterator<HashMap>& rhs) const
{
    return !(*this == rhs);
}

template <typename HashMap>
class hash_map_iterator : public const_hash_map_iterator<HashMap>
{
public:
    using value_type = typename const_hash_map_iterator<HashMap>::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type*;
    using reference = value_type&;
    using list_iterator_type = typename HashMap::ListType::const_iterator;

    hash_map_iterator() = default;
    hash_map_iterator(size_t bucket, list_iterator_type listIt, HashMap* hashmap);

    value_type& operator*();
    value_type* operator->();

    hash_map_iterator<HashMap>& operator++();
    hash_map_iterator<HashMap> operator++(int);
    
    hash_map_iterator<HashMap>& operator--();
    hash_map_iterator<HashMap> operator--(int);
};

template <typename HashMap>
hash_map_iterator<HashMap>::hash_map_iterator(size_t bucket, list_iterator_type listIt, HashMap* hashmap)
    : const_hash_map_iterator<HashMap>(bucket, listIt, hashmap)
{
}

template <typename HashMap>
typename hash_map_iterator<HashMap>::value_type& 
    hash_map_iterator<HashMap>::operator*()
{
    return const_cast<value_type&>(*this->mListIterator);
}

template <typename HashMap>
typename hash_map_iterator<HashMap>::value_type* 
    hash_map_iterator<HashMap>::operator->()
{
    return const_cast<value_type*>(&(*this->mListIterator));
}

template <typename HashMap>
hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator++()
{
    this->increment();
    return *this;
}

template <typename HashMap>
hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator++(int)
{
    auto oldIt = *this;
    this->increment();
    return oldIt;
}

template <typename HashMap>
hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator--()
{
    this->decrement();
    return *this;
}

template <typename HashMap>
hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator--(int)
{
    auto oldIt = *this;
    this->decrement();
    return oldIt;
}