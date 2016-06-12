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

    ListValue()
        : Value(Value::Type::List)
    { }

    const std::vector<ValuePtr>& asList() const override { return list; }

    bool operator==(const Value& rhs) const override;
    operator bool() const override { return !list.empty(); }

    std::ostream& show(std::ostream& out) const override;

  private:
    const std::vector<ValuePtr> list;
};

} // namespace ast

} // namespace vfn
