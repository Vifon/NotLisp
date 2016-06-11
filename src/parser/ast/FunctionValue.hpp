// File: FunctionValue.hpp
#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Return.hpp"
#include "Value.hpp"
#include "VoidValue.hpp"

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

    const FunctionValue& asFunction() const override
    {
        return *this;
    }

    ValuePtr call(Scope& scope, const std::vector<ValuePtr>& arg_values) const
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

    std::ostream& show(std::ostream& out) const override
    {
        return out << "fun(.." << args.size() << "..)";
    }

  private:
    std::vector<std::string> args;
    NodePtr body;
};

} // namespace ast

} // namespace vfn
