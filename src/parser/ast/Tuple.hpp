// File: Tuple.hpp
#pragma once

#include <vector>

#include "Node.hpp"
#include "ListValue.hpp"

namespace vfn {

namespace ast {

class Tuple : public Node
{
  public:
    Tuple(std::vector<NodePtr>&& subtrees)
        : subtrees(std::move(subtrees))
    { }

    Tuple() { }

    ValuePtr evaluate() override
    {
        std::vector<ValuePtr> evaluated{subtrees.size()};
        for (auto& subtree : subtrees) {
            evaluated.push_back(subtree->evaluate());
        }
        return ValuePtr{new ListValue{std::move(evaluated)}};
    }

  private:
    std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
