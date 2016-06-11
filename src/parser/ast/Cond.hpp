// File: Cond.hpp
#pragma once

#include <memory>

#include "Block.hpp"
#include "Node.hpp"
#include "Value.hpp"

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

    Cond(NodePtr&& condition, NodePtr&& block)
        : condition(std::move(condition))
        , block(std::move(block))
        , else_block(new VoidValue)
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        Scope new_scope{scope};
        if (*condition->evaluate(new_scope)) {
            return block->evaluate(new_scope);
        } else {
            return else_block->evaluate(new_scope);
        }
    }

  private:
    NodePtr condition;
    NodePtr block;
    NodePtr else_block;
};

} // namespace ast

} // namespace vfn
