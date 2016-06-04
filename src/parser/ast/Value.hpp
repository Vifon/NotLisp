// File: Value.hpp
#pragma once

#include <vector>

#include "bad_result_cast.hpp"
#include "Node.hpp"

namespace vfn {

namespace ast {

class Value : public Node
{
  public:
    enum class Type {
        Function,
        Int,
        List,
        Void,
    };

    virtual ~Value() { }

    virtual int asInt() const
    {
        throw bad_result_cast("Not an integer");
    }

    virtual const std::vector<ValuePtr>& asList() const
    {
        throw bad_result_cast("Not a list");
    }

    virtual bool operator==(const Value& rhs) const
    {
        return type == rhs.type;
    }

    operator bool() const override
    {
        return true;
    }

    const Type type;

  protected:
    Value(Type type)
        : type(type)
    { }
};

} // namespace ast

} // namespace vfn
