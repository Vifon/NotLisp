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

    ValuePtr evaluate(Scope& scope) override
    {
        ValuePtr evaluated_list{list->evaluate(scope)};

        std::vector<ValuePtr> filtered;
        filtered.reserve(evaluated_list->asList().size());

        for (auto& element : evaluated_list->asList()) {
            if (*fun->evaluate(scope)->asFunction().call(scope, {element})) {
                filtered.push_back(element->evaluate(scope));
            }
        }

        return ValuePtr{new ListValue{std::move(filtered)}};
    }

  private:
    NodePtr fun;
    NodePtr list;
};

} // namespace ast

} // namespace vfn
