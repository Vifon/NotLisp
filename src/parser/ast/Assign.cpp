// File: Assign.cpp

#include "Assign.hpp"

namespace vfn {

namespace ast {

Assign::Assign(const std::string& variable, NodePtr&& value)
    : variable(variable)
    , value(std::move(value))
{ }

ValuePtr Assign::evaluate(Scope& scope) const
{
    return scope.lookup(variable) = evalOnlyValue(scope);
}

ValuePtr Assign::evalOnlyValue(Scope& scope) const
{
    return value->evaluate(scope);
}

} // namespace ast

} // namespace vfn
