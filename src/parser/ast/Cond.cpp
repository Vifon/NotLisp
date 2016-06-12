// File: Cond.cpp

#include "Cond.hpp"

#include "Void.hpp"

namespace vfn {

namespace ast {

Cond::Cond(NodePtr&& condition, NodePtr&& block)
    : Cond(
        std::move(condition),
        std::move(block),
        Node::make<Void>())
{ }


ValuePtr Cond::evaluate(Scope& scope) const
{
    Scope new_scope{scope};
    if (*condition->evaluate(new_scope)) {
        return block->evaluate(new_scope);
    } else {
        return else_block->evaluate(new_scope);
    }
}

} // namespace ast

} // namespace vfn
