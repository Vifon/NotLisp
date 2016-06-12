// File: Return.cpp

#include "Return.hpp"

#include "Void.hpp"

namespace vfn {

namespace ast {

Return::Return()
    : expr(Node::make<Void>())
{ }

ValuePtr Return::evaluate(Scope& scope) const
{
    throw UglyHack(expr->evaluate(scope));
}

} // namespace ast

} // namespace vfn
