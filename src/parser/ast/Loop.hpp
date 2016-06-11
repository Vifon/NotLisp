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
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        auto list = collection->evaluate(scope);

        Scope new_scope{scope};
        new_scope.addVar(iterator_name);

        for (auto& i : list->asList()) {
            new_scope.lookup(iterator_name) = i;
            block->evaluate(new_scope);
        }

        return ValuePtr{new VoidValue};
    }

  private:
    std::string iterator_name;
    ValuePtr iterator;
    NodePtr collection;
    NodePtr block;
};

} // namespace ast

} // namespace vfn
