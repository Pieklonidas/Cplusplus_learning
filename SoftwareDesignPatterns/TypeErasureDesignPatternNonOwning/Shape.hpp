#pragma once

#include <stdexcept>
#include <utility>
#include <memory>

namespace detail{

class ShapeConcept
{
public:
    virtual ~ShapeConcept() = default;
    virtual void draw() const = 0;
    virtual std::unique_ptr<ShapeConcept> clone() const = 0;
};

template <typename ShapeT, typename DrawStrategy>
class OwningShapeModel : public ShapeConcept
{
public: 
    explicit OwningShapeModel(ShapeT shape, DrawStrategy drawer)
        : shape_(std::move(shape)), drawer_(std::move(drawer))
    {}
    
    void draw() const override
    {
        drawer_(shape_);
    }

    std::unique_ptr<ShapeConcept> clone() const override
    {
        return std::make_unique<OwningShapeModel>(*this);
    }
private:
    ShapeT shape_;
    DrawStrategy drawer_;
};

} // namespace detail

class Shape
{
public:
    template <typename ShapeT, typename DrawStrategy>
    Shape(ShapeT shape, DrawStrategy drawer)
    {
        using Model = detail::OwningShapeModel<ShapeT, DrawStrategy>;
        pimpl_ = std::make_unique<Model>(std::move(shape), std::move(drawer));
    }

    Shape(const Shape& other)
        : pimpl_(other.pimpl_->clone())
    {}

    Shape& operator=(const Shape& other)
    {
        Shape copy(other);
        pimpl_.swap(copy.pimpl_);
        return *this;
    }

    ~Shape() = default;
    Shape(Shape&&) = default;
    Shape& operator=(Shape&&) = default;
private:
    std::unique_ptr<detail::ShapeConcept> pimpl_;

    friend void draw(const Shape& shape)
    {
        shape.pimpl_->draw();
    }
};

class ShapeConstRef
{
public:
    template<typename ShapeT, typename DrawStrategy>
    ShapeConstRef(ShapeT& shape, DrawStrategy& drawer)
        : shape_{ std::addressof(shape) }
        , drawer_{ std::addressof(drawer) }
        , draw_{ [](const void* shapeBytes, const void* drawerBytes)
                 {
                    const auto* shape = static_cast<const ShapeT*>(shapeBytes);
                    const auto* drawer = static_cast<const DrawStrategy*>(drawerBytes);
                    (*drawer)(*shape);
                 }}
    {}
private:
    friend void draw(const ShapeConstRef& shape)
    {
        shape.draw_(shape.shape_, shape.drawer_);
    }
    using DrawOperation = void(const void*, const void*);

    const void* shape_{ nullptr };
    const void* drawer_{ nullptr };
    DrawOperation* draw_{ nullptr };
};