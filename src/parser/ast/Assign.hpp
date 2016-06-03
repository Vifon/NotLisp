// File: Assign.hpp
#pragma once

#include "Node.hpp"
#include "VoidValue.hpp"

namespace vfn {

namespace ast {

class Assign : public Node
{
  public:
    Assign(const std::string& variable, NodePtr&& value)
        : variable(variable)
        , value(std::move(value))
    {}

    ValuePtr evaluate() override
    {
        lookup(variable) = std::move(value->evaluate());
        return ValuePtr{new VoidValue};
    }

    const std::string variable;

  private:
    NodePtr value;
};

} // namespace ast

} // namespace vfn
