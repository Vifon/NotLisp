// File: NumberValue.hpp
#pragma once

#include "Value.hpp"

namespace vfn {

namespace ast {

class NumberValue : public Value
{
  public:
    NumberValue(int n)
        : Value(Value::Type::Int)
        , value(n)
    { }

    int asInt() const override
    {
        return value;
    }

    bool operator==(const Value& rhs) const override
    {
        return Value::operator==(rhs) && asInt() == rhs.asInt();
    }

    std::ostream& show(std::ostream& out) const override
    {
        return out << value;
    }

  private:
    int value;
};

} // namespace ast

} // namespace vfn
