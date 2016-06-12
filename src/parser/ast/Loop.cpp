// File: Loop.cpp

#include "Loop.hpp"

#include "Void.hpp"

namespace vfn {

namespace ast {

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
