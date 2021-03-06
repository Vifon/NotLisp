// File: NumberValue.cpp

#include "NumberValue.hpp"

namespace vfn {

namespace ast {

NumberValue::NumberValue(int n)
    : Value(Value::Type::Int)
    , value(n)
{ }

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
