#include <iostream>
#include <cstring>
#include "ArticleCitations.hpp"
#include "Logger.hpp"
#include "RingBuffer.hpp"

#define log(...) Logger::log(__func__, "(): ", __VA_ARGS__)

RingBuffer debugBuf(7);
#define logRb(...) debugBuf.addEntry(__func__, "(): ", __VA_ARGS__)

bool isDebugSet(int argc, char* argv[])
{
    for(int i = 1; i < argc; ++i)
    {
        if(std::strcmp(argv[i], "-d") == 0)
        {
            return true;
        }
    }
    return false;
}

class ComplicatedClass {};
std::ostream& operator<<(std::ostream& ostr, const ComplicatedClass& src)
{
    ostr << "ComplicatedClass";
    return ostr;
}

class UserCommand {};
std::ostream& operator<<(std::ostream& ostr, const UserCommand& src)
{
    ostr << "UserCommand";
    return ostr;
}

UserCommand getNextCommand(ComplicatedClass*)
{
    UserCommand cmd;
    return cmd;
}

void processUserCommand(UserCommand&)
{
    std::cout << "Processing user's command" << std::endl;
}

void trickyFunction(ComplicatedClass* obj)
{
    log("given argument: ", *obj);

    for(size_t i = 0; i < 5; ++i)
    {
        UserCommand cmd = getNextCommand(obj);
        log("retrieved cmd ", i, ": ", cmd);
        try
        {
            processUserCommand(cmd);
        }
        catch(const std::exception& e)
        {
            log("exception from processUserCommand(): ", e.what());
        }
        
    }
}

void startTimeDebugModeExample(int argc, char* argv[])
{
    Logger::enableLogging(isDebugSet(argc, argv));
    if(Logger::isLoggingEnabled())
    {
        for(int i = 0; i < argc; ++i)
        {
            log(argv[i]);
        }
    }
    ComplicatedClass obj;
    trickyFunction(&obj);
}

void trickyFunctionRb(ComplicatedClass* obj)
{
    logRb("given argument: ", *obj);

    for(size_t i = 0; i < 10; ++i)
    {
        UserCommand cmd = getNextCommand(obj);
        logRb("retrieved cmd ", i, ": ", cmd);
        try
        {
            processUserCommand(cmd);
        }
        catch(const std::exception& e)
        {
            logRb("exception from processUserCommand(): ", e.what());
        }
        
    }
}

void ringBufferExample(int argc, char* argv[])
{
    for(int i = 0; i < argc; ++i)
    {
        logRb(argv[i]);
    }
    
    ComplicatedClass obj;
    trickyFunctionRb(&obj);

    std::cout << debugBuf;
}

void processCitations(ArticleCitations cit)
{
    std::cout << cit.getArticle() << std::endl;
    int num = cit.getNumCitations();
    for(int i = 0; i < num; ++i)
    {
        std::cout << cit.getCitation(i) << std::endl;;
    }
}

void articleCitationsExample()
{
    while (true)
    {
        std::cout << "Enter a file name (\"STOP\" to stop): ";
        std::string fileName;
        std::cin >> fileName;
        if(fileName == "STOP")
        {
            break;
        }

        ArticleCitations cit(fileName);
        processCitations(cit);
    }
    
}

int main(int argc, char* argv[])
{
    // ringBufferExample(argc, argv);
    articleCitationsExample();
    return 0;
}