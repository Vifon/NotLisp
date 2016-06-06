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

    std::ostream& show(std::ostream& out) const override
    {
        return out << "()";
    }
};

} // namespace ast

} // namespace vfn
