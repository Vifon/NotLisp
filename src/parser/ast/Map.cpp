// File: Map.cpp

#include "Map.hpp"

#include <vector>

#include "ListValue.hpp"
#include "FunctionValue.hpp"

namespace vfn {

namespace ast {

ValuePtr Map::evaluate(Scope& scope) const
{
    ValuePtr evaluated_list{list->evaluate(scope)};

    std::vector<ValuePtr> mapped;
    mapped.reserve(evaluated_list->asList().size());

    for (auto& element : evaluated_list->asList()) {
        mapped.push_back(fun->evaluate(scope)->asFunction().call(scope, {element->evaluate()}));
    }

    return Value::make<ListValue>(std::move(mapped));
}

} // namespace ast

} // namespace vfn
