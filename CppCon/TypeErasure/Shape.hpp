#pragma once
#include <utility>
#include <iostream>
#include <memory>
#include "Circle.hpp"
#include "Square.hpp"

void serialize(const Circle& obj)
{
    std::cout << "Serializing circle with radius: " << obj.getRadius() << std::endl; 
}

void draw(const Circle& obj)
{
    std::cout << "Drawing circle with radius: " << obj.getRadius() << std::endl; 
}

void serialize(const Square& obj)
{
    std::cout << "Serializing square with radius: " << obj.getSide() << std::endl; 
}

void draw(const Square& obj)
{
    std::cout << "Drawing square with radius: " << obj.getSide() << std::endl; 
}

class Shape
{
private:
    struct ShapeConcept
    {
        virtual ~ShapeConcept() = default;

        virtual void serialize() const = 0;
        virtual void draw() const = 0;
        virtual std::unique_ptr<ShapeConcept> clone() const = 0;
    };

    template <typename T>
    struct ShapeModel : ShapeConcept
    {
        ShapeModel(const T& value)
            : object{value} {}
        
        std::unique_ptr<ShapeConcept> clone() const override
        {
            return std::make_unique<ShapeModel>(*this);
        }

        void serialize() const override
        {
            ::serialize(object);
        }

        void draw() const override
        {
            ::draw(object);
        }

        T object;
    };

    friend void serialize(const Shape& shape)
    {
        shape.pimpl->serialize();
    }

    friend void draw(const Shape& shape)
    {
        shape.pimpl->draw();
    }
    
    std::unique_ptr<ShapeConcept> pimpl;
public:
    template <typename T>
    Shape(T const& x)
        : pimpl(std::make_unique<ShapeModel<T>>(x))
    {}

    Shape(const Shape& s) : pimpl(s.pimpl->clone()) {}
    Shape& operator=(const Shape& s)
    {
        if (this != &s)
        {
            pimpl = s.pimpl->clone();
        }
        return *this;
    }
    Shape(Shape&& s) = default;
    Shape& operator=(Shape&& s) = default;
};


