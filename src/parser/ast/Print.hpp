// File: Print.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Print : public Node
{
  public:
    Print(NodePtr&& expr);

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const NodePtr expr;
};

} // namespace ast

} // namespace vfn
