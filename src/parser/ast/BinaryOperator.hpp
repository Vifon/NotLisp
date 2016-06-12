// File: BinaryOperator.hpp
#pragma once

#include <sstream>

#include "../../lexer/tokens/keyword.hpp"
#include "Node.hpp"

namespace vfn {

namespace ast {

class BinaryOperator : public Node
{
  public:
    BinaryOperator(Keyword op, NodePtr&& lhs, NodePtr&& rhs)
        : op(op)
        , lhs(std::move(lhs))
        , rhs(std::move(rhs))
    { }

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const Keyword op;
    const NodePtr lhs;
    const NodePtr rhs;
};

} // namespace ast

} // namespace vfn
