// File: BinaryOperator.cpp

#include "BinaryOperator.hpp"

#include "ListValue.hpp"
#include "NumberValue.hpp"
#include "Void.hpp"

namespace vfn {

namespace ast {

ValuePtr BinaryOperator::evaluate(Scope& scope) const
{
    ValuePtr lhs_val = lhs->evaluate(scope);
    ValuePtr rhs_val = rhs->evaluate(scope);
    ValuePtr result;

    switch (op) {
    case Keyword::Equals:
        if (*lhs_val == *rhs_val) {
            result = Value::make<Void>();
        } else {
            result = Value::make<ListValue>();
        }
        break;
    case Keyword::NotEquals:
        result = Value::make<NumberValue>(!(*lhs_val == *rhs_val));
        break;
    case Keyword::Plus:
        result = Value::make<NumberValue>(lhs_val->asInt() + rhs_val->asInt());
        break;
    case Keyword::Minus:
        result = Value::make<NumberValue>(lhs_val->asInt() - rhs_val->asInt());
        break;
    case Keyword::Mult:
        result = Value::make<NumberValue>(lhs_val->asInt() * rhs_val->asInt());
        break;
    case Keyword::Div:
        result = Value::make<NumberValue>(lhs_val->asInt() / rhs_val->asInt());
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
