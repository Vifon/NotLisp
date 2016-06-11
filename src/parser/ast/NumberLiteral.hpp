// File: NumberLiteral.hpp
#pragma once

#include "Node.hpp"
#include "NumberValue.hpp"

namespace vfn {

namespace ast {

class NumberLiteral : public Node
{
  public:
    NumberLiteral(int n)
        : value(n)
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        return std::make_shared<NumberValue>(value);
    }

  private:
    int value;
};

} // namespace ast

} // namespace vfn
