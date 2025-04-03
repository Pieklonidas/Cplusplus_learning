#pragma once

#include "StrongType.hpp"
#include "Printable.hpp"

using Surname = StrongType<std::string, struct SurnameTag, Printable>;