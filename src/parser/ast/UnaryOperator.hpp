// File: UnaryOperator.hpp
#pragma once

#include <sstream>

#include "Node.hpp"
#include "NumberValue.hpp"

namespace vfn {

namespace ast {

class UnaryOperator : public Node
{
  public:
    UnaryOperator(Keyword op, NodePtr&& operand)
        : op(op)
        , operand(std::move(operand))
    {}

    ValuePtr evaluate() override
    {
        ValuePtr value = operand->evaluate();
        ValuePtr result;

        switch (op) {
        case Keyword::Minus:
            result.reset(new NumberValue(-value->asInt()));
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
