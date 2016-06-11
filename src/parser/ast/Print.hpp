// File: Print.hpp
#pragma once

#include <iostream>

#include "Node.hpp"
#include "VoidValue.hpp"

namespace vfn {

namespace ast {

class Print : public Node
{
  public:
    Print(NodePtr&& expr)
        : expr(std::move(expr))
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        std::cout << *expr->evaluate(scope) << std::endl;
        return ValuePtr{new VoidValue};
    }

  private:
    NodePtr expr;
};

} // namespace ast

} // namespace vfn
