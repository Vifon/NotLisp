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
    {
        this->expr->parent = this;
    }

    ValuePtr evaluate() override
    {
        // TODO: ostream operator<< for all Values
        std::cout << expr->evaluate()->asInt() << std::endl;
        return ValuePtr{new VoidValue};
    }

  private:
    NodePtr expr;
};

} // namespace ast

} // namespace vfn
