#include <iostream>
#include <vector>
#include <limits>
#include <functional>
#include <string_view>
#include "RoundRobin.hpp"

class Process final
{
public:
    Process(std::string_view name) : mName(name) {}
    void doWorkDuringTimeSlice()
    {
        std::cout << "Process " << mName << " performing work during time slice." << std::endl;
    }

    bool operator==(const Process& rhs)
    {
        return mName == rhs.mName;
    }
private:
    std::string mName;
};
class Scheduler final
{
public:
    Scheduler(const std::vector<Process>& processes);
    void scheduleTimeSlice();
    void removeProcess(const Process& process);
private:
    RoundRobin<Process> mProcesses;
};

template<typename T>
void printVector(const std::vector<T>& v)
{
    for (auto& element : v) { std::cout << element << " "; }
    std::cout << std::endl;
}

void vectorExample1()
{
    std::vector<double> doubleVector{123.451, 365.12, 2134.165, 823.832, 12.34};
    double max = -std::numeric_limits<double>::infinity();

    for(size_t i = 0; i < doubleVector.size(); i++)
    {
        if(doubleVector[i] > max)
        {
            max = doubleVector[i];
        }
    }

    max /= 100.0;
    for(auto& element : doubleVector)
    {
        element /= max;
        std::cout << element << " ";
    }

    std::cout << std::endl;
}

void vectorExample2()
{
    std::vector<double> doubleVector;
    double max = -std::numeric_limits<double>::infinity();

    for(size_t i = 0; true; i++)
    {
        double temp;
        std::cout << "Enter score " << i << " (-1 to stop): ";
        std::cin >> temp;
        if(temp == -1)
        {
            break;
        }
        doubleVector.push_back(temp);
        if(temp > max)
        {
            max = temp;
        }
    }

    max /= 100.0;
    for(auto& element : doubleVector)
    {
        element /= max;
        std::cout << element << " ";
    }

    std::cout << std::endl;
}

void vectorExample3()
{
    std::vector<int> vectorOne(10);
    std::vector<int> vectorTwo(10);

    if(vectorOne == vectorTwo)
    {
        std::cout << "Equal!\n";
    }
    else
    {
        std::cout << "Not equal!\n";
    }
    
    vectorOne[3] = 50;

    if(vectorOne < vectorTwo)
    {
        std::cout << "vectorOne is less than vectorTwo\n";
    }
    else
    {
        std::cout << "vectorOne is not less than vectorTwo\n";
    }

    std::vector<int> vectorThree(11);
    if(vectorThree > vectorTwo)
    {
        std::cout << "vectorThree is greater than vectorTwo\n";
    }
    else
    {
        std::cout << "vectorThree is less than vectorTwo\n";
    }
}

void vectorExample4()
{
    std::string str1 = "Hello";
    std::string str2 = "World";

    std::vector<std::reference_wrapper<std::string>> vec{ ref(str1) };
    vec.push_back(std::ref(str2));
    vec[1].get() += "!\n";

    std::cout << str1 << " " << str2;
}

void vectorExample5()
{
    std::vector<int> vectorOne = { 1, 2, 3, 5 };
    std::vector<int> vectorTwo;

    vectorOne.insert(cbegin(vectorOne) + 3, 4);

    for(int i = 6; i <= 10; ++i)
    {
        vectorTwo.push_back(i);
    }
    printVector(vectorOne);
    printVector(vectorTwo);

    vectorOne.insert(cend(vectorOne), cbegin(vectorTwo), cend(vectorTwo));
    printVector(vectorOne);

    vectorOne.erase(cbegin(vectorOne) + 1, cbegin(vectorOne) + 5);
    printVector(vectorOne);

    vectorTwo.clear();
    vectorTwo.insert(cbegin(vectorTwo), 10, 100);

    vectorTwo.pop_back();
    printVector(vectorTwo);
}

void vectorExample6()
{
    std::vector<Process> processes = { Process("1"), Process("2"), Process("3") };
    Scheduler scheduler(processes);
    for(int i = 0; i < 4; ++i)
    {
        scheduler.scheduleTimeSlice();
    }

    scheduler.removeProcess(processes[1]);
    std::cout << "Remove second process" << std::endl;
    for(int i = 0; i < 4; ++i)
    {
        scheduler.scheduleTimeSlice();
    }
    scheduler.removeProcess(processes[0]);
    scheduler.removeProcess(processes[2]);
    scheduler.scheduleTimeSlice();
}

int main()
{
    // vectorExample1();
    // vectorExample2();
    // vectorExample3();
    // vectorExample4();
    // vectorExample5();
    vectorExample6();
    return 0;
}

Scheduler::Scheduler(const std::vector<Process>& processes)
{
    for(auto& process : processes)
    {
        mProcesses.add(process);
    }
}

void Scheduler::scheduleTimeSlice()
{
    try
    {
        mProcesses.getNext().doWorkDuringTimeSlice();
    }
    catch(const std::out_of_range&)
    {
        std::cerr << "No more processes to schedule." << std::endl;
    }
}

void Scheduler::removeProcess(const Process& process)
{
    mProcesses.remove(process);
}