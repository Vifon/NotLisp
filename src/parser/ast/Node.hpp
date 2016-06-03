// File: Node.hpp
#pragma once

namespace vfn {

namespace ast {

class Result;
using ResultPtr = std::unique_ptr<Result>;

class Node
{
  public:
    virtual ~Node() { }

    virtual ResultPtr evaluate() const = 0;

  protected:
    // Node& parent;

    // virtual Result& lookup(const std::string& varname)
    // {
    //     return parent.lookup(varname);
    // }

    // virtual void addVar(const std::string& varname) {
    //     parent.addVar(varname);
    // }
};

using NodePtr = std::unique_ptr<Node>;

} // namespace ast

} // namespace vfn
