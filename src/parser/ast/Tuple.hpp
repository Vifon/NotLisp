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

    ValuePtr evaluate(Scope& scope) override
    {
        std::vector<ValuePtr> evaluated;
        evaluated.reserve(subtrees.size());

        for (auto& subtree : subtrees) {
            evaluated.push_back(subtree->evaluate(scope));
        }

        return ValuePtr{new ListValue{std::move(evaluated)}};
    }

  private:
    std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
