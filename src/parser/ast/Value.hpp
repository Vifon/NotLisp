// File: Value.hpp
#pragma once

#include <ostream>
#include <memory>
#include <vector>

#include "bad_result_cast.hpp"
#include "Node.hpp"

namespace vfn {

namespace ast {

class FunctionValue;

class Value
    : public Node
    , public std::enable_shared_from_this<Value>
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

    virtual const FunctionValue& asFunction() const
    {
        throw bad_result_cast("Not a function");
    }

    virtual bool operator==(const Value& rhs) const
    {
        return type == rhs.type;
    }

    operator bool() const override
    {
        return true;
    }

    ValuePtr evaluate() override
    {
        return shared_from_this();
    }

    virtual std::ostream& show(std::ostream& out) const
    {
        throw bad_result_cast("Not showable");
    }

    const Type type;

  protected:
    Value(Type type)
        : type(type)
    { }
};

std::ostream& operator<<(std::ostream& out, const Value& value);

} // namespace ast

} // namespace vfn
