// File: Loop.hpp
#pragma once

#include <memory>

#include "Node.hpp"
#include "Value.hpp"

namespace vfn {

namespace ast {

class Loop : public Node
{
  public:
    Loop(NodePtr&& iterator, NodePtr&& collection, NodePtr&& block)
        : iterator(std::move(iterator))
        , collection(std::move(collection))
        , block(std::move(block))
    { }

    ValuePtr evaluate() override
    {
        // TODO
    }

  private:
    NodePtr iterator;
    NodePtr collection;
    NodePtr block;
};

} // namespace ast

} // namespace vfn
