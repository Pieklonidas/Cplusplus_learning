#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

class RingBuffer
{
public:
    explicit RingBuffer(size_t numEntries = kDefaultNumEntries,
                        std::ostream* ostr = nullptr);
    virtual ~RingBuffer() = default;

    template <typename... Args>
    void addEntry(const Args&... args)
    {
        std::ostringstream os;
        ((os << args), ...);
        addStringEntry(os.str());
    }

    friend std::ostream& operator<<(std::ostream& ostr, RingBuffer& rb);

    std::ostream* setOutput(std::ostream* newOstr);
private:
    std::vector<std::string> mEntries;
    std::vector<std::string>::iterator mNext;

    std::ostream* mOstr;
    bool mWrapped;
    
    static const size_t kDefaultNumEntries = 500;

    void addStringEntry(std::string&& entry);
};