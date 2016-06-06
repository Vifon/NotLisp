// File: ListValue.hpp
#pragma once

#include <vector>

#include "Value.hpp"

namespace vfn {

namespace ast {

class ListValue : public Value
{
  public:
    ListValue(std::vector<ValuePtr>&& list)
        : Value(Value::Type::List)
        , list(std::move(list))
    {
        for (auto& node : this->list) {
            node->parent = this;
        }
    }

    ListValue()
        : Value(Value::Type::List)
    { }

    const std::vector<ValuePtr>& asList() const override
    {
        return list;
    }

    bool operator==(const Value& rhs) const override
    {
        return Value::operator==(rhs) && asList() == rhs.asList();
    }

    ValuePtr evaluate() override
    {
        return shared_from_this();
    }

    operator bool() const override
    {
        return !list.empty();
    }

  private:
    std::vector<ValuePtr> list;
};

} // namespace ast

} // namespace vfn
