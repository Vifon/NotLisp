// File: Call.hpp
#pragma once

#include <string>

#include "FunctionValue.hpp"
#include "Node.hpp"
#include "Tuple.hpp"
#include "VoidValue.hpp"

namespace vfn {

namespace ast {

class Call : public Node
{
  public:
    Call(const std::string& function, NodePtr&& args)
        : function_name(function)
        , arguments_tuple(std::move(args))
    {
        this->arguments_tuple->parent = this;
    }

    Call(const std::string& function)
        : function_name(function)
        , arguments_tuple(new Tuple)
    { }

    ValuePtr evaluate() override
    {
        ValuePtr fun = lookup(function_name)->evaluate();
        return fun->asFunction().call(arguments_tuple->evaluate()->asList());
    }

  private:
    const std::string function_name;
    NodePtr arguments_tuple;
};

} // namespace ast

} // namespace vfn
