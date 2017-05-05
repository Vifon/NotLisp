// File: Filter.cpp

#include "Filter.hpp"

#include <vector>

#include "FunctionValue.hpp"
#include "ListValue.hpp"

namespace vfn {

namespace ast {

Filter::Filter(NodePtr&& fun, NodePtr&& list)
    : fun(std::move(fun))
    , list(std::move(list))
{ }

ValuePtr Filter::evaluate(Scope& scope) const
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

} // namespace ast

} // namespace vfn
