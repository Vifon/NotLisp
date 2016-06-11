// File: Value.hpp
#pragma once

#include <ostream>
#include <memory>
#include <vector>

#include "bad_result_cast.hpp"

namespace vfn {

namespace ast {

class Value;
using ValuePtr = std::shared_ptr<Value>;

class FunctionValue;

class Value : public std::enable_shared_from_this<Value>
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

    virtual operator bool() const
    {
        return true;
    }

    ValuePtr evaluate()
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
