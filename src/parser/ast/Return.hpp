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
    {
        this->expr->parent = this;
    }

    Return()
        : expr(new VoidValue)
    {
        this->expr->parent = this;
    }

    ValuePtr evaluate() override
    {
        throw UglyHack(expr->evaluate());
    }

  private:
    NodePtr expr;
};

} // namespace ast

} // namespace vfn
