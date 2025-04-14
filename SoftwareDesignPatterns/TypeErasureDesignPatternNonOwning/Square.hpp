#pragma once

class Square
{
public:
    explicit Square(double side)
        : side_(side)
    {}
    double side() const { return side_; }
private:
    double side_;
};