// File: Loop.hpp
#pragma once

#include "Node.hpp"

namespace vfn {

namespace ast {

class Loop : public Node
{
  public:
    Loop(const std::string& iterator_name, NodePtr&& collection, NodePtr&& block);

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const std::string iterator_name;
    const ValuePtr iterator;
    const NodePtr collection;
    const NodePtr block;
};

} // namespace ast

} // namespace vfn
