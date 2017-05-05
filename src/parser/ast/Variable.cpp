// File: Variable.cpp

#include "Variable.hpp"

namespace vfn {

namespace ast {

Variable::Variable(const std::string& varname)
    : name(varname)
{ }

ValuePtr Variable::evaluate(Scope& scope) const
{
    return scope.lookup(name);
}

} // namespace ast

} // namespace vfn
