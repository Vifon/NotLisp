// File: Call.hpp
#pragma once

#include <string>

#include "FunctionValue.hpp"
#include "Node.hpp"
#include "Tuple.hpp"

namespace vfn {

namespace ast {

class Call : public Node
{
  public:
    Call(const std::string& function, NodePtr&& args)
        : function_name(function)
        , arguments_tuple(std::move(args))
    { }

    Call(const std::string& function)
        : function_name(function)
        , arguments_tuple(Node::make<Tuple>())
    { }

    ValuePtr evaluate(Scope& scope) override
    {
        ValuePtr fun = scope.lookup(function_name)->evaluate();
        return fun->asFunction().call(scope, arguments_tuple->evaluate()->asList());
    }

  private:
    const std::string function_name;
    NodePtr arguments_tuple;
};

} // namespace ast

} // namespace vfn
