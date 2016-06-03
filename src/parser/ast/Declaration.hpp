// File: Declaration.hpp
#pragma once

#include <memory>

#include "Node.hpp"
#include "Value.hpp"

namespace vfn {

namespace ast {

class Declaration : public Node
{
  public:
    Declaration(std::unique_ptr<Assign>&& assignment)
        : assignment(std::move(assignment))
    {
        addVar(assignment->variable);
    }

    ValuePtr evaluate() override
    {
        return assignment->evaluate();
    }

  private:
    std::unique_ptr<Assign> assignment;
};

} // namespace ast

} // namespace vfn
