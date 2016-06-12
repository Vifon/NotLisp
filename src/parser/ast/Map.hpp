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
    { }

    ValuePtr evaluate(Scope& scope) const override
    {
        ValuePtr evaluated_list{list->evaluate(scope)};

        std::vector<ValuePtr> mapped;
        mapped.reserve(evaluated_list->asList().size());

        for (auto& element : evaluated_list->asList()) {
            mapped.push_back(fun->evaluate(scope)->asFunction().call(scope, {element->evaluate()}));
        }

        return Value::make<ListValue>(std::move(mapped));
    }

  private:
    const NodePtr fun;
    const NodePtr list;
};

} // namespace ast

} // namespace vfn
