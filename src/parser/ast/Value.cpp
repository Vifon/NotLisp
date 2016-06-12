// File: Value.cpp

#include "Value.hpp"

#include "bad_result_cast.hpp"

namespace vfn {

namespace ast {

std::ostream& operator<<(std::ostream& out, const Value& value)
{
    return value.show(out);
}

int Value::asInt() const
{
    throw bad_result_cast("Not an integer");
}

const std::vector<ValuePtr>& Value::asList() const
{
    throw bad_result_cast("Not a list");
}

const FunctionValue& Value::asFunction() const
{
    throw bad_result_cast("Not a function");
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
    throw bad_result_cast("Not showable");
}

} // namespace ast

} // namespace vfn
