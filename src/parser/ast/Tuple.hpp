// File: Tuple.hpp
#pragma once

#include <memory>
#include <vector>

#include "Node.hpp"

namespace vfn {

namespace ast {

class Tuple : public Node
{
  public:
    Tuple(std::vector<NodePtr>&& subtrees)
        : subtrees(std::move(subtrees))
    {}

    ResultPtr evaluate() const override
    {
        std::vector<ResultPtr> evaluated{subtrees.size()};
        for (auto& subtree : subtrees) {
            evaluated.push_back(subtree->evaluate());
        }
        return ResultPtr{new ListResult{std::move(evaluated)}};
    }

  private:
    std::vector<NodePtr> subtrees;
};

} // namespace ast

} // namespace vfn
