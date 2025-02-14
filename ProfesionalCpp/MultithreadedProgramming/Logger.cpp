#include "Logger.hpp"
#include <fstream>
#include <iostream>

Logger::Logger()
{
    mThread = std::thread{ &Logger::processEntries, this };
}

Logger::~Logger()
{
    {
        std::unique_lock lock(mMutex);
        mExit = true;
        mCondVar.notify_all();
    }

    mThread.join();
}

void Logger::log(std::string_view entry)
{
    std::unique_lock lock(mMutex);
    mQueue.push(std::string(entry));
    mCondVar.notify_all();
}

void Logger::processEntries()
{
    std::ofstream logFile("log.txt");
    if(logFile.fail())
    {
        std::cerr << "Failed to open logfile" << std::endl;
        return;
    }

    std::unique_lock lock(mMutex);
    while (true)
    {
        if(!mExit)
        {
            mCondVar.wait(lock);
        }

        lock.unlock();
        while (true)
        {
            lock.lock();
            if (mQueue.empty())
            {
                break;
            }
            else
            {
                logFile << mQueue.front() << std::endl;
                mQueue.pop();
            }
            lock.unlock();
        }
        if(mExit)
        {
            break;
        }
    }
    
}