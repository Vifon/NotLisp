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
    Loop(const std::string& iterator_name, NodePtr&& collection, NodePtr&& block)
        : iterator_name(std::move(iterator_name))
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
            iterator = i;
            block->evaluate();
        }

        return ValuePtr{new VoidValue};
    }

    ValuePtr& lookup(const std::string& varname) override
    {
        if (varname == iterator_name) {
            return iterator;
        } else {
            return Node::lookup(varname);
        }
    }

  private:
    std::string iterator_name;
    ValuePtr iterator;
    NodePtr collection;
    NodePtr block;
};

} // namespace ast

} // namespace vfn
