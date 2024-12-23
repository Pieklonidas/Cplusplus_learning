#include <iostream>
#include <vector>
#include <limits>
#include <functional>
#include <string_view>
#include <list>
#include <forward_list>
#include <array>
#include "RoundRobin.hpp"
#include "PacketBuffer.hpp"
#include "ErrorCorrelator.hpp"

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

void listExample1()
{
    std::list<std::string> dictionary { "aardvark", "ambulance" };
    std::list<std::string> bWords { "bathos", "balderdash" };
    dictionary.push_back("canticle");
    dictionary.push_back("consumerism");
    if(!bWords.empty())
    {
        auto iterLastB = --(cend(bWords));
        auto it = cbegin(dictionary);
        for(; it != cend(dictionary); ++it)
        {
            std::cout << "word from dictionary: " << *it << std::endl;
            if(*it > *iterLastB)
            {
                break;
            }
        }
        dictionary.splice(it, bWords);
    }
    for(const auto& word : dictionary)
    {
        std::cout << word << std::endl;
    }
}

std::list<std::string> getTotalEnrollment(const std::vector<std::list<std::string>>& courseStudents,
                                          const std::list<std::string>& droppedStudents)
{
    std::list<std::string> allStudents;
    for (auto& lst : courseStudents)
    {
        allStudents.insert(cend(allStudents), cbegin(lst), cend(lst));
    }

    allStudents.sort();

    allStudents.unique();

    for(auto& str : droppedStudents)
    {
        allStudents.remove(str);
    }
    return allStudents;
}

void listExample2()
{
    std::list<std::string> students = getTotalEnrollment({ {"Kacper", "Kacha", "Adi", "Damian", "Jedrzej", "Tomek"}, 
                                                           {"Tymek", "Hania", "Adi", "Janek", "Jedrzej", "Mati", "Nati"} },
                                                           { "Kacper", "Adi", "Tymek" });
    for(auto& str : students)
    {
        std::cout << str << std::endl;
    }
}

void forwardListExample()
{
    std::forward_list<int> list1 = { 5, 6 };
    std::forward_list<int> list2 = { 1, 2, 3, 4 };
    std::forward_list<int> list3 = { 7, 8, 9 };

    list1.splice_after(list1.before_begin(), list2);
    list1.push_front(0);

    auto iter = list1.before_begin();
    auto iterTemp = iter;
    while(++iterTemp != end(list1))
    {
        ++iter;
    }
    list1.insert_after(iter, cbegin(list3), cend(list3));
    for(auto& i : list1)
    {
        std::cout << i << ' ';
    }
}

void arrayExample()
{
    std::array<int, 3> arr = { 9, 8, 7};
    std::cout << "Array size = " << arr.size() << std::endl;
    for(const auto& i : arr)
    {
        std::cout << i << std::endl;
    }
    std::cout << "Performing arr.fill(3)..." << std::endl;
    arr.fill(3);
    for(auto iter = cbegin(arr); iter != cend(arr); ++iter)
    {
        std::cout << *iter << std::endl;
    }
}

void queueExample()
{
    PacketBuffer<IPPacket> ipPackets(3);
    for(int i = 1; i <= 4; ++i)
    {
        if(!ipPackets.bufferPacket(IPPacket(i)))
        {
            std::cout << "Packet " << i << " dropped (queue is full)." << std::endl;
        }
    }

    while (true)
    {
        try
        {
            IPPacket packet = ipPackets.getNextPacket();
            std::cout << "Processing packet " << packet.getID() << std::endl;
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << e.what() << '\n';
            break;
        }
    }
}

void priorityQueueExample()
{
    ErrorCorrelator ec;
    ec.addError(Error(3, "Unable to read file"));
    ec.addError(Error(1, "Incorrect entry from user"));
    ec.addError(Error(10, "Unable to allocate memory!"));

    while (true) {
        try {
            Error e = ec.getError();
            std::cout << e << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
            break;
        }
    }
}

int main()
{
    // vectorExample1();
    // vectorExample2();
    // vectorExample3();
    // vectorExample4();
    // vectorExample5();
    // vectorExample6();
    // listExample1();
    // listExample2();
    // forwardListExample();
    // arrayExample();
    // queueExample();
    priorityQueueExample();
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