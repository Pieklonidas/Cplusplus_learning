#pragma once

class Money
{
public:
    Money(double amount)
        : amount_(amount)
    {}

    double getAmount() const { return amount_; }
private:
    double amount_;
};

Money operator*(Money money, double factor)
{
    return Money(money.getAmount()*factor);
}

Money operator+(Money lhs, Money rhs)
{
    return Money(lhs.getAmount() + rhs.getAmount());
}