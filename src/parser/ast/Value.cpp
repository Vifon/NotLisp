// File: Value.cpp

#include "Value.hpp"

namespace vfn {

namespace ast {

std::ostream& operator<<(std::ostream& out, const Value& value)
{
    value.show(out);
}

} // namespace ast

} // namespace vfn
