// File: FunctionValue.hpp
#pragma once

#include <string>
#include <vector>

#include "Return.hpp"
#include "Void.hpp"

namespace vfn {

namespace ast {

class FunctionValue : public Value
{
  public:
    FunctionValue(std::vector<std::string>&& args, NodePtr&& body)
        : Value(Type::Function)
        , args(std::move(args))
        , body(std::move(body))
    { }

    FunctionValue(NodePtr&& body)
        : FunctionValue({}, std::move(body))
    { }

    const FunctionValue& asFunction() const override { return *this; }

    ValuePtr call(Scope& scope, const std::vector<ValuePtr>& arg_values) const;

    std::ostream& show(std::ostream& out) const override;

  private:
    const std::vector<std::string> args;
    const NodePtr body;
};

} // namespace ast

} // namespace vfn
