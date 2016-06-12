// File: UnaryOperator.hpp
#pragma once

#include <sstream>

#include "../../lexer/tokens/keyword.hpp"
#include "Node.hpp"

namespace vfn {

namespace ast {

class UnaryOperator : public Node
{
  public:
    UnaryOperator(Keyword op, NodePtr&& operand)
        : op(op)
        , operand(std::move(operand))
    { }

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const Keyword op;
    const NodePtr operand;
};

} // namespace ast

} // namespace vfn
