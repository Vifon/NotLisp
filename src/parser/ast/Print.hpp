// File: Print.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Print : public Node
{
  public:
    Print(NodePtr&& expr)
        : expr(std::move(expr))
    {}

    ValuePtr evaluate() override
    {
        // TODO: cout
    }

  private:
    NodePtr expr;
};

} // namespace ast

} // namespace vfn
