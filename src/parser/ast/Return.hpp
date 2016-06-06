// File: Return.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Return : public Node
{
  public:
    Return(NodePtr&& expr)
        : expr(std::move(expr))
    {
        this->expr->parent = this;
    }

    ValuePtr evaluate() override
    {
        // TODO
        return expr->evaluate();
    }

    bool isReturn() const override
    {
        return true;
    }

  private:
    NodePtr expr;
};

} // namespace ast

} // namespace vfn
