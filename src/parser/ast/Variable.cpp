// File: Variable.cpp

#include "Variable.hpp"

namespace vfn {

namespace ast {

ValuePtr Variable::evaluate(Scope& scope) const
{
    return scope.lookup(name);
}

} // namespace ast

} // namespace vfn
