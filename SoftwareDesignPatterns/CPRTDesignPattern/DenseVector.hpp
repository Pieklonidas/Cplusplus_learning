#pragma once

template <typename Derived>
struct DenseVector
{
protected:
    ~DenseVector() = default;
public:
    Derived& derived() { return static_cast<Derived&>(*this); }
    const Derived& derived() const { return static_cast<const Derived&>(*this); }

    size_t size() const { return derived().size(); }
};
