#include "RingBuffer.hpp"
#include <stdexcept>
#include <iterator>
#include <utility>


RingBuffer::RingBuffer(size_t numEntries, std::ostream* ostr)
    : mEntries(numEntries), mOstr(ostr), mWrapped(false)
{
    if(numEntries == 0)
    {
        throw std::invalid_argument("Number of entries must be > 0.");
    }
    mNext = begin(mEntries);
}

void RingBuffer::addStringEntry(std::string&& entry)
{
    if(mOstr)
    {
        *mOstr << entry << std::endl;
    }

    *mNext = std::move(entry);
    ++mNext;

    if(mNext == end(mEntries))
    {
        mNext = begin(mEntries);
        mWrapped = true;
    }
}

std::ostream* RingBuffer::setOutput(std::ostream* newOstr)
{
    return std::exchange(mOstr, newOstr);
}

std::ostream& operator<<(std::ostream& ostr, RingBuffer& rb)
{
    if(rb.mWrapped)
    {
        std::copy(rb.mNext, end(rb.mEntries), std::ostream_iterator<std::string>(ostr, "\n"));
    }
    std::copy(begin(rb.mEntries), rb.mNext, std::ostream_iterator<std::string>(ostr, "\n"));

    return ostr;
}