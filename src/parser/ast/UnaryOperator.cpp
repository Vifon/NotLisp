// File: UnaryOperator.cpp

#include "UnaryOperator.hpp"

#include "NumberValue.hpp"

namespace vfn {

namespace ast {

UnaryOperator::UnaryOperator(Keyword op, NodePtr&& operand)
    : op(op)
    , operand(std::move(operand))
{ }

ValuePtr UnaryOperator::evaluate(Scope& scope) const
{
    ValuePtr value = operand->evaluate(scope);
    ValuePtr result;

    switch (op) {
    case Keyword::Minus:
        result = Value::make<NumberValue>(-value->asInt());
        break;
    default:
        std::stringstream ss{"Invalid operator: "};
        ss << op;
        throw std::runtime_error(ss.str());
    }

    return result;
}

} // namespace ast

} // namespace vfn
