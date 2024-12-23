#pragma once

#include <queue>
#include <stdexcept>

template <typename T>
class PacketBuffer
{
public:
    PacketBuffer(size_t maxSize = 0);
    virtual ~PacketBuffer() = default;

    bool bufferPacket(const T& packet);

    T getNextPacket();
private:
    std::queue<T> mPackets;
    size_t mMaxSize;
};

template <typename T>
PacketBuffer<T>::PacketBuffer(size_t maxSize) : mMaxSize(maxSize)
{
}

template <typename T>
bool PacketBuffer<T>::bufferPacket(const T& packet)
{
    if(mMaxSize > 0 && mPackets.size() == mMaxSize)
    {
        return false;
    }
    mPackets.push(packet);
    return true;
}

template <typename T>
T PacketBuffer<T>::getNextPacket()
{
    if(mPackets.empty())
    {
        throw std::out_of_range("Buffer is empty");
    }

    T temp = mPackets.front();
    mPackets.pop();
    return temp;
}

class IPPacket final
{
    public:
        IPPacket(int id) : mID(id) {}
        int getID() const { return mID; }
    private:
        int mID;
};
