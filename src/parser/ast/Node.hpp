// File: Node.hpp
#pragma once

#include "Result.hpp"

namespace vfn {

namespace ast {

class Node
{
  public:
    virtual ~Node() { }

    virtual ResultPtr evaluate() const = 0;
};

} // namespace ast

} // namespace vfn
