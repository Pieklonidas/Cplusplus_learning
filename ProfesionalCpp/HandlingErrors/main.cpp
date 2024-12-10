#include <iostream>
#include <vector>
#include "FileOpenError.hpp"
#include "FileReadError.hpp"
#include "MyException.hpp"
#include <fstream>

std::vector<int> readIntegerFile(std::string_view fileName)
{
    std::ifstream inputStream(fileName.data());
    if(inputStream.fail())
    {
        throw FileOpenError(fileName);
    }

    std::vector<int> integers;
    size_t lineNumber = 0;
    while(!inputStream.eof())
    {
        std::string line;
        std::getline(inputStream, line);
        ++lineNumber;

        std::istringstream lineStream(line);

        int temp;
        while (lineStream >> temp)
        {
            integers.push_back(temp);
        }

        if(!lineStream.eof())
        {
            throw FileReadError(fileName, lineNumber);
        }
    }
    return integers;
}

void firstExample()
{
    std::vector<int> myInts;
    std::string fileName;
    std::cout << "Provide fileName:\n";
    std::cin >> fileName;
    try
    {
        myInts = readIntegerFile(fileName);
    }
    catch(const FileError& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    
    for(const auto& val : myInts)
    {
        std::cout << val << std::endl;
    }
}

void doSomething()
{
    try
    {
        throw std::runtime_error("Throwing a runtime_error exception");
    }
    catch(const std::runtime_error& e)
    {
        std::cout << __func__ << " caught a runtime_error" << std::endl;
        std::cout << __func__ << " throwing MyException" << std::endl;
        std::throw_with_nested(MyException("MyException with nested runtime_error"));
    }
}

void secondExample()
{
    try
    {
        doSomething();
    }
    catch(const MyException& e)
    {
        std::cout << __func__ << " caught MyException: " << e.what() << std::endl;

        const auto* pNested = dynamic_cast<const std::nested_exception*>(&e);
        if(pNested)
        {
            try
            {
                pNested->rethrow_nested();
            }
            catch(const std::runtime_error& e)
            {
                std::cout << " Nested exception: " << e.what() << std::endl;
            }
        }
    }
}

void g() { throw std::invalid_argument("Some exception invalid argument"); }

void f() 
{ 
    try
    {
        g();
    } 
    catch(const std::invalid_argument& e)
    {
        std::cout << "caught in f: " << e.what() << std::endl;
        throw;
    }
}

void thirdExample()
{
    try
    {
        f();
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Caught in main: " << e.what() << std::endl;
    }
}
int main()
{
    // firstExample();    
    // secondExample();
    thirdExample();
    return 0;
}