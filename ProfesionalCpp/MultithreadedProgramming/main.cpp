#include <iostream>
#include <thread>
#include <functional>
#include <stdexcept>
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

int main()
{
    // threadExampleFunction();
    // threadExampleFunctionObject();
    // threadExampleLambda();
    // threadExampleMemberFunction();
    threadExceptionsExample();
    return 0;
}