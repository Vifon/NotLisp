// File: Print.hpp
#pragma once

#include <iostream>

#include "Node.hpp"
#include "Void.hpp"

namespace vfn {

namespace ast {

class Print : public Node
{
  public:
    Print(NodePtr&& expr)
        : expr(std::move(expr))
    { }

    ValuePtr evaluate(Scope& scope) const override
    {
        std::cout << *expr->evaluate(scope) << std::endl;
        return Value::make<Void>();
    }

  private:
    const NodePtr expr;
};

} // namespace ast

} // namespace vfn
