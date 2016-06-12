// File: Filter.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Filter : public Node
{
  public:
    Filter(NodePtr&& fun, NodePtr&& list)
        : fun(std::move(fun))
        , list(std::move(list))
    { }

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const NodePtr fun;
    const NodePtr list;
};

} // namespace ast

} // namespace vfn
