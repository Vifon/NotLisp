// File: Call.cpp

#include "Call.hpp"

#include "FunctionValue.hpp"
#include "Tuple.hpp"

namespace vfn {

namespace ast {

Call::Call(const std::string& function, NodePtr&& args)
    : function_name(function)
    , arguments_tuple(std::move(args))
{ }

Call::Call(const std::string& function)
    : function_name(function)
    , arguments_tuple(Node::make<Tuple>())
{ }

ValuePtr Call::evaluate(Scope& scope) const
{
    ValuePtr fun = scope.lookup(function_name);
    return fun->asFunction().call(scope, arguments_tuple->evaluate(scope)->asList());
}

} // namespace ast

} // namespace vfn
