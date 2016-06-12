// File: NumberValue.cpp

#include "NumberValue.hpp"

namespace vfn {

namespace ast {

bool NumberValue::operator==(const Value& rhs) const
{
    return Value::operator==(rhs) && asInt() == rhs.asInt();
}


std::ostream& NumberValue::show(std::ostream& out) const
{
    return out << value;
}

} // namespace ast

} // namespace vfn
