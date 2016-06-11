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

    const std::vector<ValuePtr>& asList() const override
    {
        return list;
    }

    bool operator==(const Value& rhs) const override
    {
        return Value::operator==(rhs) && asList() == rhs.asList();
    }

    operator bool() const override
    {
        return !list.empty();
    }

    std::ostream& show(std::ostream& out) const override
    {
        if (list.empty()) {
            out << "[]";
        } else {
            auto it = list.begin();
            out << "[" << **it++;
            while (it != list.end()) {
                out << ", " << **it++;
            }
            out << "]";
        }
        return out;
    }

  private:
    std::vector<ValuePtr> list;
};

} // namespace ast

} // namespace vfn
