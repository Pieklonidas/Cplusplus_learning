#include <iostream>
#include <regex>
#include <string>
#include <vector>

void regexMatchExample()
{
    std::regex r("(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])");
    while (true)
    {
        std::cout << "Enter a date (year/month/day) (q=quit): ";
        std::string str;
        if(!std::getline(std::cin, str) || str == "q")
        {
            break;
        }

        std::smatch m;
        if(std::regex_match(str, m, r))
        {
            int year = std::stoi(m[1]);
            int month = std::stoi(m[2]);
            int day = std::stoi(m[3]);
            std::cout << "  Valid date: Year=" << year
                      << ", month=" << month
                      << ", day=" << day << std::endl;
            std::cout << "Full date: " << m[0] << std::endl;
        }
        else
        {
            std::cout << "  Invalid date." << std::endl;
        }
    }
}

void regexSearchExample()
{
    std::regex r("//\\s*(.+)$");
    while (true)
    {
        std::cout << "Enter a string with optional code comments (q=quit): ";
        std::string str;
        if (!std::getline(std::cin, str) || str == "q")
        {
            break;
        }
        
        std::smatch m;
        if(std::regex_search(str, m, r))
        {
            std::cout << "  Found comment '" << m[1] << "'" << std::endl;
            std::cout << "  Full '" << m[0] << "'" << std::endl;
            std::cout << "  Before: " << m.prefix() << std::endl;
        }
        else
        {
            std::cout << "  No comment found!" << std::endl;
        }
    }
    
}

void regexIteratorExample()
{
    std::regex reg("[\\w]+");
    while (true)
    {
        std::cout << "Enter a string to split (q=quit): ";
        std::string str;
        if(!std::getline(std::cin, str) || str == "q")
        {
            break;
        }

        const std::sregex_iterator end;
        for(std::sregex_iterator iter(cbegin(str), cend(str), reg); iter != end; ++iter)
        {
            std::cout << "\"" << (*iter)[0] << "\"" << std::endl;
        }
    }
}

void regexTokenIteratorExample()
{
    std::regex reg("^(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])$");
    while (true)
    {
        std::cout << "Enter a date (year/month/day) (q=quit): ";
        std::string str;
        if(!std::getline(std::cin, str) || str == "q")
        {
            break;
        }

        std::vector<int> indices{ 2, 3 };
        const std::sregex_token_iterator end;
        for(std::sregex_token_iterator iter(cbegin(str), cend(str), reg, indices); iter != end; ++iter)
        {
            std::cout << "\"" << *iter << "\"" << std::endl;
        }
    }

    std::regex reg2(R"(\s*[,;]\s*)");
    while (true)
    {
        std::cout << "Enter a string to split on ',' and ';' (q=quit): ";
        std::string str;
        if (!std::getline(std::cin, str) || str == "q")
            break;

        const std::sregex_token_iterator end;
        for(std::sregex_token_iterator iter(cbegin(str), cend(str), reg2, -1); iter != end; ++iter)
        {
            std::cout << "\"" << *iter << "\"" << std::endl;
        }
    }
    
}

void regexReplaceExample()
{
    const std::string str("<body><h1>Header</h1><p>Some text</p></body>");
    std::regex r("<h1>(.*)</h1><p>(.*)</p>");

    const std::string format("H1=$1 and P=$2");
    std::string result = std::regex_replace(str, r, format);

    std::cout << "Original string: '" << str << "'" << std::endl;
    std::cout << "New string     : '" << result << "'" << std::endl;
}

int main()
{
    // regexMatchExample();
    // regexSearchExample();
    // regexIteratorExample();
    // regexTokenIteratorExample();
    regexReplaceExample();
    return 0;
}