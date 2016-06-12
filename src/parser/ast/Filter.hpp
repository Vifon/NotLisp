// File: Filter.hpp
#pragma once

#include "ListValue.hpp"
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

    ValuePtr evaluate(Scope& scope) const override
    {
        ValuePtr evaluated_list{list->evaluate(scope)};

        std::vector<ValuePtr> filtered;
        filtered.reserve(evaluated_list->asList().size());

        for (auto& element : evaluated_list->asList()) {
            if (*fun->evaluate(scope)->asFunction().call(scope, {element})) {
                filtered.push_back(element->evaluate());
            }
        }

        return Value::make<ListValue>(std::move(filtered));
    }

  private:
    const NodePtr fun;
    const NodePtr list;
};

} // namespace ast

} // namespace vfn
