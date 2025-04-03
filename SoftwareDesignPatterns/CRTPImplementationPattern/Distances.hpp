#pragma once

#include "StrongType.hpp"
#include "Addable.hpp"
#include "Printable.hpp"

template<typename T>
using Meter = StrongType<T, struct MeterTag, Addable, Printable>;

template<typename T>
using Kilometer = StrongType<T, struct KilometerTag, Addable, Printable>;