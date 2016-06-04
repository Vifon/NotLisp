// File: Node.hpp
#pragma once

#include <stdexcept>

namespace vfn {

namespace ast {

class Value;
using ValuePtr = std::unique_ptr<Value>;

class Node
{
  public:
    virtual ~Node() { }

    virtual ValuePtr evaluate() = 0;

    virtual operator bool() const
    {
        throw std::runtime_error("Not castable");
    }

  protected:
    // Node& parent;

    virtual ValuePtr& lookup(const std::string& varname)
    {
        // return parent.lookup(varname);
    }

    virtual void addVar(const std::string& varname) {
        // parent.addVar(varname);
    }
};

using NodePtr = std::unique_ptr<Node>;

} // namespace ast

} // namespace vfn

#include "Value.hpp"      // Warning: Tricky order-dependent includes!
