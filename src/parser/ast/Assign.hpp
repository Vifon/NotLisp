// File: Assign.hpp
#pragma once

#include <string>

#include "Node.hpp"

namespace vfn {

namespace ast {

class Assign : public Node
{
  public:
    Assign(const std::string& variable, NodePtr&& value)
        : variable(variable)
        , value(std::move(value))
    { }

    ValuePtr evaluate(Scope& scope) const override;
    ValuePtr evalOnlyValue(Scope& scope) const;

    const std::string variable;

  private:
    const NodePtr value;
};

} // namespace ast

} // namespace vfn
