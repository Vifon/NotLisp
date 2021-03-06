// File: Variable.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Variable : public Node
{
  public:
    Variable(const std::string& varname);

    ValuePtr evaluate(Scope& scope) const override;

    const std::string name;
};

} // namespace ast

} // namespace vfn
