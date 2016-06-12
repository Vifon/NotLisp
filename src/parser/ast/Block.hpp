// File: Block.hpp
#pragma once

#include <vector>

#include "Node.hpp"

namespace vfn {

namespace ast {

class Block : public Node
{
  public:
    Block(std::vector<NodePtr>&& subtrees)
        : subtrees(std::move(subtrees))
    { }

    Block() { }

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
