// File: Tuple.cpp

#include "Tuple.hpp"

#include "ListValue.hpp"

namespace vfn {

namespace ast {

Tuple::Tuple(std::vector<NodePtr>&& subtrees)
    : subtrees(std::move(subtrees))
{ }

ValuePtr Tuple::evaluate(Scope& scope) const
{
    std::vector<ValuePtr> evaluated;
    evaluated.reserve(subtrees.size());

    for (auto& subtree : subtrees) {
        evaluated.push_back(subtree->evaluate(scope));
    }

    return Value::make<ListValue>(std::move(evaluated));
}

} // namespace ast

} // namespace vfn
