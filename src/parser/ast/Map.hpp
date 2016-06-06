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
        ValuePtr evaluated_list{list->evaluate()};

        std::vector<ValuePtr> mapped;
        mapped.reserve(evaluated_list->asList().size());

        for (auto& element : evaluated_list->asList()) {
            mapped.push_back(fun->evaluate()->asFunction().call({element->evaluate()}));
        }

        return ValuePtr{new ListValue{std::move(mapped)}};
    }

  private:
    NodePtr fun;
    NodePtr list;
};

} // namespace ast

} // namespace vfn
