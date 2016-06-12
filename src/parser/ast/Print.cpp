// File: Print.cpp

#include "Print.hpp"

#include <iostream>

#include "Void.hpp"

namespace vfn {

namespace ast {

ValuePtr Print::evaluate(Scope& scope) const
{
    std::cout << *expr->evaluate(scope) << std::endl;
    return Value::make<Void>();
}

} // namespace ast

} // namespace vfn
