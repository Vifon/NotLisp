// File: Variable.hpp
#pragma once

#include "Node.hpp"
#include "Void.hpp"

namespace vfn {

namespace ast {

class Variable : public Node
{
  public:
    Variable(const std::string& varname)
        : name(varname)
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        return scope.lookup(name);
    }

    const std::string name;
};

} // namespace ast

} // namespace vfn
