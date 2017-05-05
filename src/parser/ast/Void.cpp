// File: Void.cpp

#include "Void.hpp"

namespace vfn {

namespace ast {

Void::Void()
    : Value(Value::Type::Void)
{ }

ValuePtr Void::evaluate(Scope&) const
{
    return Value::evaluate();
}

std::ostream& Void::show(std::ostream& out) const
{
    return out << "()";
}

} // namespace ast

} // namespace vfn
