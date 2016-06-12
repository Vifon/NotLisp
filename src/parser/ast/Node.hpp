// File: Node.hpp
#pragma once

#include <memory>

#include "Scope.hpp"
#include "Value.hpp"

namespace vfn {

namespace ast {

class Node
{
  public:
    virtual ~Node() { }

    virtual ValuePtr evaluate(Scope& scope) = 0;

    ValuePtr evaluate();

  protected:
    Node() { }
};

using NodePtr = std::unique_ptr<Node>;

} // namespace ast

} // namespace vfn
