// File: Literal.hpp
#pragma once

#include "Node.hpp"
#include "NumberValue.hpp"
#include "Value.hpp"

namespace vfn {

namespace ast {

class Literal : public Node
{
  public:
    Literal(ValuePtr&& value)
        : value(value)
    { }

    Literal(int number)
        : Literal(std::make_shared<NumberValue>(number))
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
