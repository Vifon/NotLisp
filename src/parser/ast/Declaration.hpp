// File: Declaration.hpp
#pragma once

#include <memory>

#include "Assign.hpp"
#include "Node.hpp"

namespace vfn {

namespace ast {

class Declaration : public Node
{
  public:
    Declaration(std::unique_ptr<Assign>&& assignment)
        : assignment(std::move(assignment))
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        ValuePtr result = assignment->evalOnlyValue(scope);
        return scope.addVar(assignment->variable) = std::move(result);
    }

  private:
    std::unique_ptr<Assign> assignment;
};

} // namespace ast

} // namespace vfn
