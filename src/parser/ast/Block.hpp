// File: Block.hpp
#pragma once

#include "Node.hpp"

#include <memory>
#include <vector>

namespace vfn {

namespace ast {

class Block : public Node
{
  public:
    Block(std::vector<std::unique_ptr<Node>>&& subtrees)
        : subtrees(std::move(subtrees))
    {}

    void evaluate() const override
    {
        for (auto& subtree : subtrees) {
            subtree->evaluate();
        }
    }

  private:
    std::vector<std::unique_ptr<Node>> subtrees;
};

} // namespace ast

} // namespace vfn
