// File: Node.hpp
#pragma once

namespace vfn {

namespace ast {

class Node
{
  public:
    virtual ~Node() { }

    virtual void evaluate() const = 0;
};

} // namespace ast

} // namespace vfn
