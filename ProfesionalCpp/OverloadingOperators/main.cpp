#include <iostream>

class Base
{
public:
    Base() = default;
    Base(int value) : value(value) {};
    int getValue() const { return value; };
    void setValue(const int newValue) { value = newValue; };
    Base operator-() const;
    Base& operator++();
    Base operator++(int);
    Base& operator--();
    Base operator--(int);
    int operator()(int param);
    operator int() const;
private:
    int value{0};
};

std::ostream& operator<<(std::ostream& ostr, const Base& base);
std::istream& operator>>(std::istream& istr, Base& base);

int main()
{
    Base b(2);
    Base b2 = -b;
    std::cout << "Testing unary minus operator, should be -2: " << b2.getValue() << std::endl;

    std::cout << "Testing prefix increment, should be 2: " << (b++).getValue() << std::endl;
    std::cout << "Testing postfix increment, should be 4: " << (++b).getValue() << std::endl;

    std::cout << "Testing prefix decrement, should be -2: " << (b2--).getValue() << std::endl;
    std::cout << "Testing postfix decrement, should be -4: " << (--b2).getValue() << std::endl;

    std::cout << "Testing insertion operator, should be 4: " << b << std::endl;
    std::cout << "Testing extraction operator:" << std::endl;
    std::cin >> b;
    std::cout << "should be a value that was provided: " << b << std::endl;
    std::cout << b(5) << std::endl;

    int conversionOperator = b;
    std::cout << "Testing conversion operator, should be the same as b value: " << conversionOperator << std::endl;

    return 0;
}

Base Base::operator-() const { return Base(-getValue()); }; // { return -getValue(); }; <- works as well

Base& Base::operator++()
{ 
    setValue(value+1);
    return *this; 
};

Base Base::operator++(int)
{ 
    auto oldBase(*this);
    ++(*this);
    return oldBase; 
};

Base& Base::operator--()
{ 
    setValue(value-1);
    return *this; 
};

Base Base::operator--(int)
{ 
    auto oldBase(*this);
    --(*this);
    return oldBase; 
};

std::ostream& operator<<(std::ostream& ostr, const Base& base)
{
    return ostr << base.getValue();
}

std::istream& operator>>(std::istream& istr, Base& base)
{
    int value;
    istr >> value;
    base.setValue(value);
    return istr;
}

int Base::operator()(int param)
{
    std::cout << "Testing function operator, should be param plus value: " << std::endl;
    return param + value;
}

Base::operator int() const
{
    return getValue();
}