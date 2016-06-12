// File: Void.cpp

#include "Void.hpp"

namespace vfn {

namespace ast {

ValuePtr Void::evaluate(Scope& scope) const
{
    return Value::evaluate();
}

std::ostream& Void::show(std::ostream& out) const
{
    return out << "()";
}

} // namespace ast

} // namespace vfn
