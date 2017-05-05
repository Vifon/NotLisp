// File: Void.hpp
#pragma once

#include "Node.hpp"
#include "Value.hpp"

namespace vfn {

namespace ast {

class Void
    : public Value
    , public Node
{
  public:
    Void();

    ValuePtr evaluate(Scope& scope) const override;

    std::ostream& show(std::ostream& out) const override;
};

} // namespace ast

} // namespace vfn
