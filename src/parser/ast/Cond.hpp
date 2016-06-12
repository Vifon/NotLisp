// File: Cond.hpp
#pragma once

#include <memory>

#include "Node.hpp"

namespace vfn {

namespace ast {

class Cond : public Node
{
  public:
    Cond(NodePtr&& condition, NodePtr&& block, NodePtr&& else_block)
        : condition(std::move(condition))
        , block(std::move(block))
        , else_block(std::move(else_block))
    { }

    Cond(NodePtr&& condition, NodePtr&& block);

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const NodePtr condition;
    const NodePtr block;
    const NodePtr else_block;
};

} // namespace ast

} // namespace vfn
