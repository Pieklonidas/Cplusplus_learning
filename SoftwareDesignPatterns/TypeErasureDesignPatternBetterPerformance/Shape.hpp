#pragma once

#include <stdexcept>
#include <utility>
#include <memory>
#include <array>
#include <cstdlib>

template <size_t Capacity = 32U, size_t Alignment = alignof(void*)>
class Shape
{
public:
    template<typename ShapeT, typename DrawStrategy>
    Shape(ShapeT shape, DrawStrategy drawer)
    {
        using Model = OwningModel<ShapeT,DrawStrategy>;

        static_assert(sizeof(Model) <= Capacity, "Given type is too large");
        static_assert(alignof(Model) <= Alignment, "Given type is misaligned");

        std::construct_at(static_cast<Model*>(pimpl())
                        , std::move(shape), std::move(drawer));
    }

    Shape(const Shape& other)
    {
        other.pimpl()->clone( pimpl() );
    }
    
    Shape& operator=(const Shape& other)
    {
        Shape copy(other);
        buffer_.swap(copy.buffer_);
        return *this;
    }

    Shape(Shape&& other) noexcept
    {
        other.pimpl()->move(pimpl());
    }

    Shape& operator=(Shape&& other) noexcept
    {
        Shape copy(std::move(other));
        buffer_.swap(copy.buffer_);
        return *this;
    }

    ~Shape()
    {
        std::destroy_at(pimpl());
    }

private:
    struct Concept
    {
        virtual ~Concept() = default;
        virtual void draw() const = 0;
        virtual void clone(Concept* memory) const = 0;
        virtual void move(Concept* memory) = 0;
    };
    
    template<typename ShapeT, typename DrawStrategy>
    struct OwningModel : public Concept
    {
        OwningModel(ShapeT shape, DrawStrategy drawer)
            : shape_(std::move(shape)), drawer_(std::move(drawer))
        {}

        void draw() const override
        {
            drawer_(shape_);
        }

        void clone(Concept* memory) const override
        {
            std::construct_at(static_cast<OwningModel*>(memory), *this);
        }

        void move(Concept* memory) override
        {
            std::construct_at(static_cast<OwningModel*>(memory), std::move(*this));
        }

        ShapeT shape_;
        DrawStrategy drawer_;
    };

    Concept* pimpl()
    {
        return reinterpret_cast<Concept*>(buffer_.data());
    }

    const Concept* pimpl() const
    {
        return reinterpret_cast<const Concept*>(buffer_.data());
    }

    friend void draw(Shape shape)
    {
        shape.pimpl()->draw();
    }

    alignas(Alignment) std::array<std::byte, Capacity> buffer_;
};