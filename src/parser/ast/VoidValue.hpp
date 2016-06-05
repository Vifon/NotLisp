// File: VoidValue.hpp
#pragma once

#include "Value.hpp"

namespace vfn {

namespace ast {

class VoidValue : public Value
{
  public:
    VoidValue()
        : Value(Value::Type::Void)
    { }

    ValuePtr evaluate() override
    {
        return shared_from_this();
    }
};

} // namespace ast

} // namespace vfn
