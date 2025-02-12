#include <iostream>
#include <thread>
#include <functional>
#include <stdexcept>
#include <atomic>
#include <chrono>
#include <mutex>
#include "Counter.hpp"
#include "Request.hpp"

void counter(int id, int numIterations)
{
    for(int i = 0; i < numIterations; ++i)
    {
        std::cout << "Counter " << id << " has value " << i << std::endl;
    }
}

void threadExampleFunction()
{
    std::thread t1(counter, 1, 6);
    std::thread t2(counter, 2, 4);
    t1.join();
    t2.join();
}

void threadExampleLambda()
{
    int id = 1;
    int numIterations = 5;
    std::thread t1([id, numIterations]
        {
            for(int i = 0; i < numIterations; ++i)
            {
                std::cout << "Counter " << id << " has value " << i << std::endl;
            }
        });

    t1.join();
}

void threadExampleFunctionObject()
{
    std::thread t1{ Counter{ 1, 20 } };

    Counter c(2, 12);
    std::thread t2(c);

    std::thread t3(Counter(3,10));

    t1.join();
    t2.join();
    t3.join();
}

void threadExampleMemberFunction()
{
    Request req(100);
    std::thread t1{ &Request::process, &req };
    t1.join();
}

void doSomeWork()
{
    for(int i = 0; i < 5; ++i)
    {
        std::cout << i << std::endl;
    }
    std::cout << "Thread throwing a runtime_error exception..." << std::endl;
    throw std::runtime_error("Exception from thread");
}

void threadFunc(std::exception_ptr& err)
{
    try
    {
        doSomeWork();
    }
    catch(...)
    {
        std::cout << "Thread caught exception, returning exception..." << std::endl;
        err = std::current_exception();
    }    
}

void doWorkInThread()
{
    std::exception_ptr error;
    std::thread t{ threadFunc, std::ref(error) };
    t.join();

    if(error)
    {
        std::cout << "Main thread received exception, rethrowing it..." << std::endl;
        std::rethrow_exception(error);
    }
    else
    {
        std::cout << "Main thread did not receive any exception." << std::endl;
    }
}

void threadExceptionsExample()
{
    try
    {
        doWorkInThread();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Main function caught: '" << e.what() << "'" << '\n';
    }
    
}

using namespace std::chrono_literals;

void increment(int& counter)
{
    for(int i = 0; i < 100; i++)
    {
        ++counter;
        std::this_thread::sleep_for(1ms);
    }
}

void incrementAtomic(std::atomic<int>& counter)
{
    for(int i = 0; i < 100; ++i)
    {
        ++counter;
        std::this_thread::sleep_for(1ms);
    }
}

void AtomicExample()
{   
    int counter = 0;
    std::vector<std::thread> threads;
    for(int i = 0; i < 10; ++i)
    {
        threads.push_back(std::thread{ increment, std::ref(counter) });
    }

    for(auto& t : threads)
    {
        t.join();
    }
    std::cout << "Result for data race = " << counter << std::endl;

    std::atomic<int> counterAtomic(0);
    std::vector<std::thread> threadsAtomic;
    for(int i = 0; i < 10; ++i)
    {
        threadsAtomic.push_back(std::thread{ incrementAtomic, std::ref(counterAtomic) });
    }

    for(auto& t : threadsAtomic)
    {
        t.join();
    }
    std::cout << "Result for data race = " << counterAtomic << std::endl;
}

void AtomicOperationsExample()
{
    std::atomic<int> value(10);
    std::cout << "Value = " << value << std::endl;
    int fetched = value.fetch_add(4);
    std::cout << "Fetched = " << fetched << std::endl;
    std::cout << "Value = " << value << std::endl;
}

std::once_flag gOnceFlag;

void initializeSharedResources()
{
    std::cout << "Shared resources initialized." << std::endl;
}

void processingFunction()
{
    std::call_once(gOnceFlag, initializeSharedResources);

    std::cout << "Processing" << std::endl;
}

void callOnceExample()
{
    std::vector<std::thread> threads(3);
    for(auto& t : threads)
    {
        t = std::thread{ processingFunction };
    }

    for(auto& t : threads)
    {
        t.join();
    }
}

std::atomic<bool> gInitialized(false);
std::mutex gMutex;

void processingFunction2()
{
    if(!gInitialized)
    {
        std::unique_lock lock(gMutex);
        if(!gInitialized)
        {
            initializeSharedResources();
            gInitialized = true;
        }
    }
    std::cout << "OK" << std::endl;
}

void doubleCheckedExample()
{
    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i)
    {
        threads.push_back(std::thread{ processingFunction2 });
    }

    for(auto& t : threads)
    {
        t.join();
    }
}

int main()
{
    // threadExampleFunction();
    // threadExampleFunctionObject();
    // threadExampleLambda();
    // threadExampleMemberFunction();
    // threadExceptionsExample();
    // AtomicExample();
    // callOnceExample();
    doubleCheckedExample();
    return 0;
}