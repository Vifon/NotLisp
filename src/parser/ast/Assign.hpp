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
    {
        this->value->parent = this;
    }

    ValuePtr evaluate() override
    {
        return lookup(variable) = evalOnlyValue();
    }

    ValuePtr evalOnlyValue()
    {
        return value->evaluate();
    }

    const std::string variable;

  private:
    NodePtr value;
};

} // namespace ast

} // namespace vfn
