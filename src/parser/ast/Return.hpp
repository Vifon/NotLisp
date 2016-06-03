// File: Return.hpp
#pragma once

#include "Node.hpp"

#include <memory>

namespace vfn {

namespace ast {

class Return : public Node
{
  public:
    Return(NodePtr&& expr)
        : expr(std::move(expr))
    {}

    ResultPtr evaluate() const override
    {
        // TODO
        std::cout << "Returning " << expr.get() << std::endl;
        return expr->evaluate();
    }

  private:
    NodePtr expr;
};

} // namespace ast

} // namespace vfn
