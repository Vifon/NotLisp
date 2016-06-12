// File: Value.cpp

#include "Value.hpp"

#include "BadResultCast.hpp"

namespace vfn {

namespace ast {

std::ostream& operator<<(std::ostream& out, const Value& value)
{
    return value.show(out);
}

int Value::asInt() const
{
    throw BadResultCast("Not an integer");
}

const std::vector<ValuePtr>& Value::asList() const
{
    throw BadResultCast("Not a list");
}

const FunctionValue& Value::asFunction() const
{
    throw BadResultCast("Not a function");
}

bool Value::operator==(const Value& rhs) const
{
    return type == rhs.type;
}

Value::operator bool() const
{
    return true;
}

std::ostream& Value::show(std::ostream& out) const
{
    throw BadResultCast("Not showable");
}

} // namespace ast

} // namespace vfn
