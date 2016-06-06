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
    {
        this->fun->parent = this;
        this->list->parent = this;
    }

    ValuePtr evaluate() override
    {
        ValuePtr evaluated_list{list->evaluate()};

        std::vector<ValuePtr> filtered;
        filtered.reserve(evaluated_list->asList().size());

        for (auto& element : evaluated_list->asList()) {
            if (*fun->evaluate()->asFunction().call({element})) {
                filtered.push_back(element->evaluate());
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
