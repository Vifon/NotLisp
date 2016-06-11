// File: Node.hpp
#pragma once

#include <stdexcept>
#include <memory>

#include "Value.hpp"
#include "Scope.hpp"

namespace vfn {

namespace ast {

class Scope;

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
