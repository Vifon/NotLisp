// File: Loop.hpp
#pragma once

#include "Node.hpp"
#include "Void.hpp"

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

    ValuePtr evaluate(Scope& scope) const override
    {
        auto list = collection->evaluate(scope);

        Scope new_scope{scope};
        new_scope.addVar(iterator_name);

        for (auto& i : list->asList()) {
            new_scope.lookup(iterator_name) = i;
            block->evaluate(new_scope);
        }

        return Value::make<Void>();
    }

  private:
    const std::string iterator_name;
    const ValuePtr iterator;
    const NodePtr collection;
    const NodePtr block;
};

} // namespace ast

} // namespace vfn
