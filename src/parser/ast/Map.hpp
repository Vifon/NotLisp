// File: Map.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Map : public Node
{
  public:
    Map(NodePtr&& fun, NodePtr&& list)
        : fun(std::move(fun))
        , list(std::move(list))
    {
        this->fun->parent = this;
        this->list->parent = this;
    }

    ValuePtr evaluate() override
    {
        // TODO
        return ValuePtr{new VoidValue};
    }

  private:
    NodePtr fun;
    NodePtr list;
};

} // namespace ast

} // namespace vfn
