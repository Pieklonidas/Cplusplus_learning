#pragma once
#include <iostream>
#include <fstream>

class Logger
{
public:
    static void enableLogging(bool enable) { msLoggingEnabled = enable; }
    static bool isLoggingEnabled() { return msLoggingEnabled; }

    template <typename... Args>
    static void log(const Args&... args)
    {
        if(!msLoggingEnabled)
        {
            return;
        }
        
        std::ofstream logfile(msDebugFileName, std::ios_base::app);
        if(logfile.fail())
        {
            std::cerr << "Unable to open debug file" << std::endl;
            return;
        }

        ((logfile << args), ...);
        logfile << std::endl;
    }
private:
    static const std::string msDebugFileName;
    static bool msLoggingEnabled;
};

const std::string Logger::msDebugFileName = "debugfile.out";
bool Logger::msLoggingEnabled = false;