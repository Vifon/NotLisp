// File: Function.hpp
#pragma once

#include "Result.hpp"

namespace vfn {

namespace ast {

class Function : public Result
{
  public:
    Function(NodePtr&& args, NodePtr&& body)
        : Result(Type::Function)
        , args(std::move(args))
        , body(std::move(body))
    {}

    ResultPtr evaluate() const override
    {
        // TODO
        return ResultPtr{new VoidResult};
    }

  private:
    NodePtr args;
    NodePtr body;
};

} // namespace ast

} // namespace vfn
