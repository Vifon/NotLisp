// File: Loop.cpp

#include "Loop.hpp"

#include "Void.hpp"

namespace vfn {

namespace ast {

Loop::Loop(const std::string& iterator_name, NodePtr&& collection, NodePtr&& block)
    : iterator_name(std::move(iterator_name))
    , collection(std::move(collection))
    , block(std::move(block))
{ }

ValuePtr Loop::evaluate(Scope& scope) const
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

} // namespace ast

} // namespace vfn
