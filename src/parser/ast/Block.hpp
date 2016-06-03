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
    {}

    ValuePtr evaluate() override
    {
        for (auto& subtree : subtrees) {
            subtree->evaluate();
        }
        return ValuePtr{new VoidValue};
    }

  private:
    std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
