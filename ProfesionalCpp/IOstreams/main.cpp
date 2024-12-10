#include "Muffin.hpp"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>

void getReservationData1()
{
    std::string questName;
    int partySize;
    std::cout << "Name and number of quests: ";
    std::cin >> questName >> partySize;
    std::cout << "Thank you, " << questName << "." << std::endl;
    if (partySize > 10)
    {
        std::cout << "An extra gratuity will apply." << std::endl;
    }
}

void getReservationData2()
{
    std::string guestName;
    int partySize = 0;
    char ch;
    std::cin >> std::noskipws;
    while(std::cin >> ch)
    {
        if(isdigit(ch))
        {
            std::cin.unget();
            if(std::cin.fail())
            {
                std::cout << "unget() failed" << std::endl;
            }
            break;
        }
        guestName += ch;
    }
    if(std::cin)
        std::cin >> partySize;
    if(!std::cin)
    {
        std::cerr << "Error getting party size." << std::endl;
        return;
    }

    std::cout << "Thank you '" << guestName << "', party of " << partySize << std::endl;
    if (partySize > 10) {
        std::cout << "An extra gratuity will apply." << std::endl;
    }
}

void getReservationData3()
{
    std::string guestName;
    int partySize = 0;
    char ch;
    std::cin >> std::noskipws;
    while(true)
    {
        ch = static_cast<char>(std::cin.peek());
        if(!std::cin)
            break;
        if(isdigit(ch))
            break;
        
        std::cin >> ch;
        if(!std::cin)
            break;
        guestName += ch;
    }
    if(std::cin)
        std::cin >> partySize;
    if(!std::cin)
    {
        std::cerr << "Error getting party size." << std::endl;
        return;
    }

    std::cout << "Thank you '" << guestName << "', party of " << partySize << std::endl;
    if (partySize > 10) {
        std::cout << "An extra gratuity will apply." << std::endl;
    }
}

std::string readName1(std::istream& stream)
{
    std::cout << "ReadName1" << std::endl;
    std::string name;
    while(stream)
    {
        int next = stream.get();
        if(!stream || next == std::char_traits<char>::eof())
            break;
        name += static_cast<char>(next);
    }
    std::cout << "ReadName1 end" << std::endl;
    return name;
}

std::string readName2(std::istream& stream)
{
    std::cout << "ReadName2" << std::endl;
    std::string name;
    char next;
    while(stream.get(next))
    {
        name += next;
    }
    std::cout << "ReadName2 end" << std::endl;
    return name;
}

void outputExample()
{
    const char* test = "hello there\n";
    std::cout.write(test, strlen(test));
    std::cout.put('a');

    bool myBool = true;
    std::cout << "This is default: " << myBool << std::endl;
    std::cout << "This should be true: " << std::boolalpha << myBool << std::endl;
    std::cout << "This should be 1: " << std::noboolalpha << myBool << std::endl;

    int i = 123;
    printf("This should be '   123': %6d\n", i);
    std::cout << "This should be '   123': " << std::setw(6) << i << std::endl;

    printf("This should be '000123': %06d\n", i);
    std::cout << "This should be '000123': " << std::setfill('0') << std::setw(6) << i << std::endl;
    std::cout << "This should be '***123': " << std::setfill('*') << std::setw(6) << i << std::endl;
    std::cout << std::setfill(' ');

    double dbl = 1.452;
    double dbl2 = 5;
    std::cout << "This should be ' 5': " << std::setw(2) << std::noshowpoint << dbl2 << std::endl;
    std::cout << "This should be '@@1.452': " << std::setw(7) << std::setfill('@') << dbl << std::endl;
    std::cout << std::setfill(' ');

    std::cout << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": " << std::quoted("Quoted string with \"embedded quotes\".") << std::endl;

    std::cout << "This should be '1.23456': " << std::setprecision(5) << 1.23456789 << std::endl;
}

void inputExample1()
{
    getReservationData1();
    std::cout << "Enter numbers on separate lines to add. Use Control+D to finish (Control+Z in Windows)." << std::endl;
    int sum = 0;
    if (!std::cin.good())
    {
        std::cerr << "Standard input is in a bad state!" << std::endl;
        return;
    }
    int number;
    while(!std::cin.bad())
    {
        std::cin >> number;
        if(std::cin.good())
        {
            sum+=number;
        }
        else if(std::cin.eof())
        {
            break;
        }
        else if(std::cin.fail())
        {
            std::cin.clear();
            std::string badToken;
            std::cin >> badToken;
            std::cerr << "WARNING: Bad input encountered: " << badToken << std::endl;
        }
    }
    std::cout << "The sum is " << sum << std::endl;
}

void inputExample2()
{
    // std::string name1 = readName1(std::cin);
    // std::cout << "name1: " << name1 << std::endl;
    // std::string name2 = readName2(std::cin);
    // std::cout << "name2: " << name2 << std::endl;
    // getReservationData2();
    getReservationData3();
}

Muffin createMuffin(std::istringstream& stream)
{
    Muffin muffin;

    std::string description;
    int size;
    bool hasChips;

    stream >> description >> size >> std::boolalpha >> hasChips;
    if(stream)
    {
        muffin.setSize(size);
        muffin.setDescription(description);
        muffin.setHasChocolateChips(hasChips);
    }
    return muffin;
}

void stringStreamsExample1()
{
    std::cout << "Enter tokens. Control+D (Unix) or Control+Z (Windows) to end" << std::endl;
    std::ostringstream outStream;
    while(std::cin)
    {
        std::string nextToken;
        std::cout << "Next token: ";
        std::cin >> nextToken;
        if(!std::cin || nextToken == "done")
        {
            break;
        }
        outStream << nextToken << "\t";
    }
    std::cout << "The end result is: " << outStream.str();
}

void stringStreamsExample2()
{
    std::string input = "Strawberry 20 true";
    std::istringstream stream(input);
    Muffin muffin = createMuffin(stream);
    std::cout << "Description: " << muffin.getDescription() << ", Size: " << muffin.getSize() 
              << std::boolalpha << ", Chips: " << muffin.hasChocolateChips();
}

void fileStreamExample1(int argc, char* argv[])
{
    std::ofstream outFile("test.txt", std::ios_base::trunc);
    if(!outFile.good())
    {
        std::cerr << "Error while opening output file!" << std::endl;
        return;
    }
    outFile << "There were " << argc << " arguments to this program." << std::endl;
    outFile << "They are: " << std::endl;
    for(int i = 0; i < argc; i++)
    {
        outFile << argv[i] << std::endl;
    }
    return;
}

void fileStreamExample2()
{
    std::ofstream fout("test.out");
    if(!fout)
    {
        std::cerr << "Error opening test.out for writing" << std::endl;
        return;
    }
    fout << "12345";
    std::streampos currPos = fout.tellp();
    if(5 == currPos)
    {
        std::cout << "Test passed: Currently at position 5" << std::endl;
    }
    else
    {
        std::cout << "Test failed: Not at position 5" << std::endl;
    }
    
    fout.seekp(2, std::ios_base::beg);
    
    fout << 0;
    fout.close();

    std::ifstream fin("test.out");
    if(!fin)
    {
        std::cerr << "Error opening test.out for reading" << std::endl;
        return;
    }

    int testVal;
    fin >> testVal;
    if(!fin)
    {
        std::cerr << "Error reading from file" << std::endl;
        return;
    }

    const int expected = 12045;
    if(testVal == expected)
    {
        std::cout << "Test passed: Value is " << expected << std::endl;
    }
    else
    {
        std::cout << "Test failed: Value is " << testVal << std::endl;
    }
}

bool changeNumberForID(std::string_view filename, int id, std::string_view newNumber)
{
    std::fstream ioData(filename.data());
    if(!ioData)
    {
        std::cerr << "Error while opening file " << filename << std::endl;
        return false;
    }
    while (ioData)
    {
        int idRead;
        std::string number;

        ioData >> idRead;
        if(!ioData)
        {
            break;
        }
        if(idRead == id)
        {
            ioData.seekp(ioData.tellg()-2);
            std::cout << "New number: " << newNumber << std::endl;
            ioData << " " << newNumber;
            break;
        }
        ioData >> number;
    }
    return true;
}

void biDirectionalIO()
{
    std::string filename;
    int id;
    std::string newNumber;
    std::cout << "Provide filename:\n";
    std::cin >> filename;
    std::cout << "Provide id:\n";
    std::cin >> id;
    std::cout << "Provide newNumber:\n";
    std::cin >> newNumber;
    changeNumberForID(filename, id, newNumber);
}

int main(int argc, char* argv[])
{
    // outputExample();
    // inputExample1();
    // inputExample2();
    // stringStreamsExample1();
    // stringStreamsExample2();
    // fileStreamExample1(argc, argv);
    // fileStreamExample2();
    biDirectionalIO();
    return 0;
}