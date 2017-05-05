// File: Tuple.hpp
#pragma once

#include <vector>

#include "Node.hpp"

namespace vfn {

namespace ast {

class Tuple : public Node
{
  public:
    Tuple(std::vector<NodePtr>&& subtrees);
    Tuple() { }

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
