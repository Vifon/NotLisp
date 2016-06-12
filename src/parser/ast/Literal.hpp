// File: Literal.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Literal : public Node
{
  public:
    Literal(ValuePtr&& value)
        : value(value)
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        return value;
    }

  private:
    ValuePtr value;
};

} // namespace ast

} // namespace vfn
