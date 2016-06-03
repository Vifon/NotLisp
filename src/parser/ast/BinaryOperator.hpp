// File: BinaryOperator.hpp
#pragma once

#include "Node.hpp"

#include <memory>
#include <sstream>

namespace vfn {

namespace ast {

class BinaryOperator : public Node
{
  public:
    BinaryOperator(Keyword op, NodePtr&& lhs, NodePtr&& rhs)
        : op(op)
        , lhs(std::move(lhs))
        , rhs(std::move(rhs))
    {}

    ResultPtr evaluate() const override
    {
        ResultPtr lhs_val = lhs->evaluate();
        ResultPtr rhs_val = rhs->evaluate();
        ResultPtr result;

        switch (op) {
        case Keyword::Equals:
            result.reset(new NumberResult(*lhs_val == *rhs_val));
            break;
        case Keyword::NotEquals:
            result.reset(new NumberResult(!(*lhs_val == *rhs_val)));
            break;
        case Keyword::Plus:
            result.reset(new NumberResult(lhs_val->asInt() + rhs_val->asInt()));
            break;
        case Keyword::Minus:
            result.reset(new NumberResult(lhs_val->asInt() - rhs_val->asInt()));
            break;
        case Keyword::Mult:
            result.reset(new NumberResult(lhs_val->asInt() * rhs_val->asInt()));
            break;
        case Keyword::Div:
            result.reset(new NumberResult(lhs_val->asInt() / rhs_val->asInt()));
            break;
        default:
            std::stringstream ss{"Invalid operator: "};
            ss << op;
            throw std::runtime_error(ss.str());
        }

        return result;
    }

  private:
    const Keyword op;
    NodePtr lhs;
    NodePtr rhs;
};

} // namespace ast

} // namespace vfn
