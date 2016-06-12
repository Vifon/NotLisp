// File: Return.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Return : public Node
{
  public:
    class UglyHack
    {
      public:
        UglyHack(ValuePtr&& value)
            : return_value(std::move(value))
        { }

        ValuePtr return_value;
    };


    Return(NodePtr&& expr)
        : expr(std::move(expr))
    { }

    Return();

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const NodePtr expr;
};

} // namespace ast

} // namespace vfn
