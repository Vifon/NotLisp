// File: Block.hpp
#pragma once

#include <vector>

#include "Node.hpp"
#include "Void.hpp"

namespace vfn {

namespace ast {

class Block : public Node
{
  public:
    Block(std::vector<NodePtr>&& subtrees)
        : subtrees(std::move(subtrees))
    { }

    Block() { }

    ValuePtr evaluate(Scope& scope) const override
    {
        ValuePtr ret = Value::make<Void>();

        Scope new_scope{scope};

        for (auto& subtree : subtrees) {
            ret = subtree->evaluate(new_scope);
        }

        return ret;
    }

  private:
    const std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
