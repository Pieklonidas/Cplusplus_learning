#pragma once
#include "CalculatorCommand.hpp"
#include <stack>
#include <memory>

class Calculator
{
public:
    void compute(std::unique_ptr<CalculatorCommand> command);
    void undoLast();

    int result() const;
    void clear();
private:
    using CommandStack = std::stack<std::unique_ptr<CalculatorCommand>>;

    int current_{};
    CommandStack stack_;
};