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
};

} // namespace ast

} // namespace vfn
