#include <iostream>
#include <vector>
#include <limits>
#include <functional>
#include <string_view>
#include <list>
#include <forward_list>
#include <array>
#include <map>
#include "RoundRobin.hpp"
#include "PacketBuffer.hpp"
#include "ErrorCorrelator.hpp"
#include "BankAccount.hpp"
#include "BuddyList.hpp"
#include "AccessList.hpp"
#include "CableCompany.hpp"

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

class Data final
{
    public:
        explicit Data(int value = 0) : mValue(value) { }
        int getValue() const { return mValue; }
        void setValue(int value) { mValue = value; }

    private:
        int mValue;
}; 

void mapExample1()
{
    std::map<int, Data> dataMap;

    auto ret = dataMap.insert({ 1, Data(4) });
    if( ret.second )
    {
        std::cout << "Insert succeeded!" << std::endl;
    }
    else
    {
        std::cout << "Insert failed" << std::endl;
    }

    
    if(auto[iter, success] = dataMap.insert(std::make_pair(1, Data(6) )); success )
    {
        std::cout << "Insert succeeded!" << std::endl;
    }
    else
    {
        std::cout << "Insert failed" << std::endl;
    }

    if(auto[iter, success] = dataMap.insert_or_assign(1, Data(7)); success)
    {
        std::cout << "Inserted!" << std::endl;
    }
    else
    {
        std::cout << "Overwritten" << std::endl;
    }
    if(auto[iter, success] = dataMap.insert_or_assign(5, Data(10)); success)
    {
        std::cout << "Inserted!" << std::endl;
    }
    else
    {
        std::cout << "Overwritten" << std::endl;
    }

    for(auto iter = cbegin(dataMap); iter != cend(dataMap); ++iter)
    {
        std::cout << iter->second.getValue() << std::endl;
    }

    auto it = dataMap.find(1);
    if(it != end(dataMap))
    {
        it->second.setValue(100);
    }
    std::cout << "After changing value for the key: 1\n";
    for(auto iter = cbegin(dataMap); iter != cend(dataMap); ++iter)
    {
        std::cout << iter->second.getValue() << std::endl;
    }
    std::cout << "There are " << dataMap.count(1) << " elements with key 1\n";
    dataMap.erase(1);
    std::cout << "There are " << dataMap.count(1) << " elements with key 1\n";

    std::map<int, Data> dataMap2;
    std::cout << "There are " << dataMap.count(5) << " elements with key 5\n";
    auto extractedNode = dataMap.extract(5);
    std::cout << "There are " << dataMap.count(5) << " elements with key 5\n";
    dataMap2.insert(std::move(extractedNode));

    for(auto iter = cbegin(dataMap2); iter != cend(dataMap2); ++iter)
    {
        std::cout << iter->second.getValue() << std::endl;
    }

    std::map<int, int> src = { {1, 11}, {2, 22} };
    std::map<int, int> dst = { {2, 23}, {3, 33}, {4, 44}, {5, 55} };
    dst.merge(src);
    for(const auto& [key, value] : src)
    {
        std::cout << "Key: " << key << " value: " << value << std::endl;
    }

    for(const auto& [key, value] : dst)
    {
        std::cout << "Key: " << key << " value: " << value << std::endl;
    }
}

void mapExample2()
{
    BankDB db;
    db.addAccount(BankAccount(100, "Nicholas Solter"));
    db.addAccount(BankAccount(200, "Scott Kleper"));

    try
    {
        auto& acct = db.findAccount(100);
        std::cout << "Found account " << acct.getAcctNum() << ", it belongs to: " << acct.getClientName() << std::endl;
        acct.setClientName("Nicholas A Solter");
        std::cout << "Found account " << acct.getAcctNum() << ", it belongs to: " << acct.getClientName() << std::endl;

        {
            auto& acct2 = db.findAccount("Scott Kleper");
            std::cout << "Found account for " << acct2.getClientName() << ", with number " << acct2.getAcctNum() << std::endl;
            acct2.setAcctNum(220);
        }

        auto& acct3 = db.findAccount(220); // We have changed number only in the Bank accout but it has no
                                           // impact on the key in the map in the Data Base, so the key stays
                                           // the same and we are not able to find the account for Scott Kleper
        std::cout << "Found account " << acct3.getAcctNum() << ", it belongs to: " << acct3.getClientName() << std::endl;

        auto& acct4 = db.findAccount(312);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void multimapExample2()
{
    BuddyList buddies;
    buddies.addBuddy("Harry Potter", "Ron Weasley");
    buddies.addBuddy("Harry Potter", "Hermione Granger");
    buddies.addBuddy("Harry Potter", "Hagrid");
    buddies.addBuddy("Harry Potter", "Hagrid");
    buddies.addBuddy("Harry Potter", "Draco Malfoy");

    buddies.removeBuddy("Harry Potter", "Draco Malfoy");
    buddies.addBuddy("Hagrid", "Harry Potter");
    buddies.addBuddy("Hagrid", "Ron Weasley");
    buddies.addBuddy("Hagrid", "Hermione Granger");

    auto harrysFriends = buddies.getBuddies("Harry Potter");

    std::cout << "Harry's friends: " << std::endl;
    for (const auto& name : harrysFriends) {
        std::cout << "\t" << name << std::endl;
    }
}

void setExample()
{
    AccessList fileX = { "pvw", "mgregoire", "baduser" };
    fileX.removeUser("baduser");

    if (fileX.isAllowed("mgregoire")) {
        std::cout << "mgregoire has permissions" << std::endl;
    }

    if (fileX.isAllowed("baduser")) {
        std::cout << "baduser has permissions" << std::endl;
    }

    auto users = fileX.getAllUsers();
    for (const auto& user : users) {
        std::cout << user << "  ";
    }
}

template <class T>
void printMap(const T& m)
{
    for(auto& [key, value] : m)
    {
        std::cout << key << " (Phone: " << value << ")" << std::endl;
    }
    std::cout << "---------------" << std::endl;
}

void unorderedMapExample()
{
    std::unordered_map<std::string, std::string> phoneBook = 
    {
        { "Marc G.", "123-456789" },
        { "Scott K.", "654-987321" }
    };

    phoneBook.insert(std::make_pair("John D.", "321-987654"));
    phoneBook["Johan G."] = "963-258147";
    phoneBook["Freddy K."] = "999-256256";
    phoneBook.erase("Freddy K.");
    printMap(phoneBook);

    const size_t bucket = phoneBook.bucket("Marc G.");
    std::cout << "Marc G. is in bucket " << bucket
              << " which contains the following "
              << phoneBook.bucket_size(bucket) << " elements:" << std::endl;
    
    auto localBegin = phoneBook.cbegin(bucket);
    auto localEnd = phoneBook.cend(bucket);
    for (auto iter = localBegin; iter != localEnd; ++iter) {
        std::cout << "\t" << iter->first << " (Phone: "
                  << iter->second << ")" << std::endl;
    }
    std::cout << "-------" << std::endl;

    std::cout << "There are " << phoneBook.bucket_count() << " buckets." << std::endl;
    std::cout << "Average number of elements in a bucket is " << phoneBook.load_factor() << std::endl;
}

void bitsetExample()
{
    CableCompany myCC;
    auto basic_pkg = "1111000000";
    auto premium_pkg = "1111111111";
    auto sports_pkg = "0000100111";

    myCC.addPackage("basic", std::bitset<kNumChannels>(basic_pkg));
    myCC.addPackage("premium", std::bitset<kNumChannels>(premium_pkg));
    myCC.addPackage("sports", std::bitset<kNumChannels>(sports_pkg));

    myCC.newCustomer("Marc G.", "basic");
    myCC.addPackageToCustomer("Marc G.", "sports");
    std::cout << myCC.getCustomerChannels("Marc G.") << std::endl;
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
    // priorityQueueExample();
    // mapExample1();
    // mapExample2();
    // multimapExample2();
    // setExample();
    // unorderedMapExample();
    bitsetExample();
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