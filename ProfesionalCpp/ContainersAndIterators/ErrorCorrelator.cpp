#include "ErrorCorrelator.hpp"
#include <stdexcept>

bool operator<(const Error& lhs, const Error& rhs)
{
    return (lhs.getPriority() < rhs.getPriority());
}

std::ostream& operator<<(std::ostream& os, const Error& err)
{
    os << err.getErrorString() << " (priority " << err.getPriority() << ")\n";
    return os;
}

void ErrorCorrelator::addError(const Error& error)
{
    mErrors.push(error);
}

Error ErrorCorrelator::getError()
{
    if(mErrors.empty())
    {
        throw std::out_of_range("No more errors.");
    }
    
    Error top = mErrors.top();
    mErrors.pop();
    return top;
}