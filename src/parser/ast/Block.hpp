// File: Block.hpp
#pragma once

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

    ValuePtr evaluate() override
    {
        ValuePtr ret{new VoidValue};;

        for (auto& subtree : subtrees) {
            ret = subtree->evaluate();
        }

        return ret;
    }

  private:
    std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
