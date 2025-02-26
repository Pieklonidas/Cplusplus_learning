#include "ArticleCitations.hpp"
#include <fstream>
#include <stdexcept>

ArticleCitations::ArticleCitations(std::string_view fileName)
    : mCitations(nullptr), mNumCitations(0)
{
    readFile(fileName);
}

ArticleCitations::ArticleCitations(const ArticleCitations& src)
{
    copy(src);
}

ArticleCitations& ArticleCitations::operator=(const ArticleCitations& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }

    delete[] mCitations;

    copy(rhs);
    return *this;
}

void ArticleCitations::copy(const ArticleCitations& src)
{
    mArticle = src.mArticle;
    mNumCitations = src.mNumCitations;
    mCitations = new std::string[mNumCitations];
    for(int i = 0; i < mNumCitations; ++i)
    {
        mCitations[i] = src.mCitations[i];
    }
}

ArticleCitations::~ArticleCitations()
{
    delete[] mCitations;
}

void ArticleCitations::readFile(std::string_view fileName)
{
    std::ifstream inputFile(fileName.data());
    if (inputFile.fail())
    {
        throw std::invalid_argument("Unable to open file");
    }
    getline(inputFile, mArticle);
    inputFile >> std::ws;
    int count = 0;
    std::streampos citationsStart = inputFile.tellg();
    while(!inputFile.eof())
    {
        inputFile >> std::ws;
        std::string temp;
        getline(inputFile, temp);
        if(!temp.empty())
        {
            count++;
        }
    }

    delete[] mCitations;
    mCitations = nullptr;
    mNumCitations = 0;
    if (count != 0)
    {
        mCitations = new std::string[count];
        mNumCitations = count;

        inputFile.clear();
        inputFile.seekg(citationsStart);

        for (count = 0; count < mNumCitations; ++count)
        {
            std::string temp;
            getline(inputFile, temp);
            if(!temp.empty())
            {
                mCitations[count] = temp;
            }
        }
    }
}