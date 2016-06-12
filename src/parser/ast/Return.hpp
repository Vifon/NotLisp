// File: Return.hpp
#pragma once

#include "Node.hpp"
#include "Void.hpp"

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

    Return()
        : expr(new Void)
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        throw UglyHack(expr->evaluate(scope));
    }

  private:
    NodePtr expr;
};

} // namespace ast

} // namespace vfn
