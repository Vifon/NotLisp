// File: UnaryOperator.hpp
#pragma once

#include "Node.hpp"

#include <memory>
#include <sstream>

namespace vfn {

namespace ast {

class UnaryOperator : public Node
{
  public:
    UnaryOperator(Keyword op, NodePtr&& operand)
        : op(op)
        , operand(std::move(operand))
    {}

    ResultPtr evaluate() const override
    {
        ResultPtr value = operand->evaluate();
        ResultPtr result;

        switch (op) {
        case Keyword::Minus:
            result.reset(new NumberResult(-value->asInt()));
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
    NodePtr operand;
};

} // namespace ast

} // namespace vfn
