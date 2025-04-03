#pragma once

template<typename T, typename Tag, template<typename> class... Skills>
struct StrongType : private Skills< StrongType<T,Tag,Skills...> >...
{
public:
    using value_type = T;

    explicit StrongType(const T& value) : value_(value) {}

    T& get() { return value_; }
    const T& get() const { return value_; }

private:
    T value_;
};