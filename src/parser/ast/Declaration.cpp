// File: Declaration.cpp

#include "Declaration.hpp"

namespace vfn {

namespace ast {

Declaration::Declaration(std::unique_ptr<Assign>&& assignment)
    : assignment(std::move(assignment))
{ }

ValuePtr Declaration::evaluate(Scope& scope) const
{
    ValuePtr result = assignment->evalOnlyValue(scope);
    return scope.addVar(assignment->variable) = std::move(result);
}

} // namespace ast

} // namespace vfn
