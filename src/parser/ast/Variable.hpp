// File: Variable.hpp
#pragma once

#include "Node.hpp"
#include "VoidValue.hpp"

namespace vfn {

namespace ast {

class Variable : public Node
{
  public:
    Variable(const std::string& varname)
        : name(varname)
    { }

    ValuePtr evaluate() override
    {
        return lookup(name);
    }

  private:
    const std::string name;
};

} // namespace ast

} // namespace vfn
