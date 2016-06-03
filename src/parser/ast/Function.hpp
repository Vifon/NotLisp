// File: Function.hpp
#pragma once

#include "Value.hpp"
#include "VoidValue.hpp"

namespace vfn {

namespace ast {

class Function : public Value
{
  public:
    Function(NodePtr&& args, NodePtr&& body)
        : Value(Type::Function)
        , args(std::move(args))
        , body(std::move(body))
    {}

    Function(NodePtr&& body)
        : Value(Type::Function)
        , body(std::move(body))
    {}

    ValuePtr evaluate() override
    {
        // TODO
        return ValuePtr{new VoidValue};
    }

  private:
    NodePtr args;
    NodePtr body;
};

} // namespace ast

} // namespace vfn
