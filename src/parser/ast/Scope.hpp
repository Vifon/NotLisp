// File: Scope.hpp
#pragma once

#include <map>
#include <string>

#include "Value.hpp"

namespace vfn {

namespace ast {

class Scope
{
  public:
    Scope();
    Scope(Scope& parent);

    ValuePtr& lookup(const std::string& varname);
    ValuePtr& addVar(const std::string& varname);

  private:
    Scope* const parent;

    std::map<std::string, ValuePtr> scope;
};

} // namespace ast

} // namespace vfn
