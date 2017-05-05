// File: Scope.cpp

#include "Scope.hpp"

#include <stdexcept>

namespace vfn {

namespace ast {

Scope::Scope()
    : parent(nullptr)
{ }

Scope::Scope(Scope& parent)
    : parent(&parent)
{ }

ValuePtr& Scope::lookup(const std::string& varname)
{
    auto it = scope.find(varname);
    if (it != scope.end()) {
        return it->second;
    } else if (parent) {
        return parent->lookup(varname);
    } else {
        throw std::runtime_error("Undeclared variable: " + varname);
    }
}

ValuePtr& Scope::addVar(const std::string& varname)
{
    if (scope.count(varname)) {
        throw std::runtime_error("Variable already declared: " + varname);
    } else {
        return scope[varname];
    }
}

} // namespace ast

} // namespace vfn
