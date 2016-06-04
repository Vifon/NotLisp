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
        // TODO: shared_ptr?
        // return ValuePtr{new ListValue{*this}};
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
