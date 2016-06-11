// File: Block.hpp
#pragma once

#include <map>
#include <stdexcept>
#include <vector>

#include "Node.hpp"
#include "VoidValue.hpp"

namespace vfn {

namespace ast {

class Block : public Node
{
  public:
    Block(std::vector<NodePtr>&& subtrees)
        : subtrees(std::move(subtrees))
    { }

    Block() { }

    ValuePtr evaluate(Scope& scope) override
    {
        ValuePtr ret{new VoidValue};;

        Scope new_scope{scope};

        for (auto& subtree : subtrees) {
            ret = subtree->evaluate(new_scope);
        }

        return ret;
    }

  private:
    std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
