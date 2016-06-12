// File: Call.hpp
#pragma once

#include <string>

#include "Node.hpp"

namespace vfn {

namespace ast {

class Call : public Node
{
  public:
    Call(const std::string& function, NodePtr&& args)
        : function_name(function)
        , arguments_tuple(std::move(args))
    { }

    Call(const std::string& function);

    ValuePtr evaluate(Scope& scope) const override;

  private:
    const std::string function_name;
    const NodePtr arguments_tuple;
};

} // namespace ast

} // namespace vfn
