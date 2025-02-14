#pragma once

#include <string>
#include <string_view>
#include <mutex>
#include <condition_variable>
#include <queue>

class Logger
{
public:
    Logger();

    Logger(const Logger& src) = delete;
    Logger& operator=(const Logger& rhs) = delete;

    virtual ~Logger();

    void log(std::string_view entry);
private:
    void processEntries();
    std::mutex mMutex;
    std::condition_variable mCondVar;
    std::queue<std::string> mQueue;
    std::thread mThread;
    bool mExit = false;
};