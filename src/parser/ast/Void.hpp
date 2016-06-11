// File: Void.hpp
#pragma once

#include "Node.hpp"
#include "Value.hpp"

namespace vfn {

namespace ast {

class Void
    : public Value
    , public Node
{
  public:
    Void()
        : Value(Value::Type::Void)
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        return Value::evaluate();
    }

    std::ostream& show(std::ostream& out) const override
    {
        return out << "()";
    }
};

} // namespace ast

} // namespace vfn
