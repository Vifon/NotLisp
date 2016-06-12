// File: Scope.hpp
#pragma once

#include <map>
#include <memory>
#include <stdexcept>

#include "Value.hpp"

namespace vfn {

namespace ast {

class Scope
{
  public:
    Scope()
        : parent(nullptr)
    { }

    Scope(Scope& parent)
        : parent(&parent)
    { }

    ValuePtr& lookup(const std::string& varname)
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

    ValuePtr& addVar(const std::string& varname)
    {
        if (scope.count(varname)) {
            throw std::runtime_error("Variable already declared: " + varname);
        } else {
            return scope[varname];
        }
    }

  private:
    Scope* const parent;

    std::map<std::string, ValuePtr> scope;
};

} // namespace ast

} // namespace vfn
