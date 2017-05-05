// File: FunctionValue.cpp

#include "FunctionValue.hpp"

#include <sstream>
#include <stdexcept>

namespace vfn {

namespace ast {

FunctionValue::FunctionValue(std::vector<std::string>&& args, NodePtr&& body)
    : Value(Type::Function)
    , args(std::move(args))
    , body(std::move(body))
{ }

FunctionValue::FunctionValue(NodePtr&& body)
    : FunctionValue({}, std::move(body))
{ }

ValuePtr FunctionValue::call(Scope& scope, const std::vector<ValuePtr>& arg_values) const
{
    if (arg_values.size() != args.size()) {
        std::stringstream ss;
        ss << args.size() << "-argument function called with "
           << arg_values.size() << " arguments";
        throw std::runtime_error(ss.str());
    } else {
        Scope new_scope{scope};

        for (size_t i = 0; i < args.size(); ++i) {
            new_scope.addVar(args[i]) = arg_values[i];
        }

        try {
            return body->evaluate(new_scope);
        } catch (Return::UglyHack& ret) {
            return std::move(ret.return_value);
        }
    }
}

std::ostream& FunctionValue::show(std::ostream& out) const
{
    return out << "fun(.." << args.size() << "..)";
}

} // namespace ast

} // namespace vfn
