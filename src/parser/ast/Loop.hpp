// File: Loop.hpp
#pragma once

#include <memory>

#include "Node.hpp"
#include "VoidValue.hpp"

namespace vfn {

namespace ast {

class Loop : public Node
{
  public:
    Loop(const std::string& iterator, NodePtr&& collection, NodePtr&& block)
        : iterator(std::move(iterator))
        , collection(std::move(collection))
        , block(std::move(block))
    {
        this->collection->parent = this;
        this->block->parent = this;
    }

    ValuePtr evaluate() override
    {
        auto list = collection->evaluate();

        for (auto& i : list->asList()) {
            block->addVar(iterator);
            block->lookup(iterator) = i;
            block->evaluate();
        }

        return ValuePtr{new VoidValue};
    }

  private:
    std::string iterator;
    NodePtr collection;
    NodePtr block;
};

} // namespace ast

} // namespace vfn
