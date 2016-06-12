// File: Value.hpp
#pragma once

#include <ostream>
#include <memory>
#include <vector>

namespace vfn {

namespace ast {

class Value;
using ValuePtr = std::shared_ptr<const Value>;

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

    template <typename T, typename ...Args>
    static ValuePtr make(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    virtual int asInt() const;
    virtual const std::vector<ValuePtr>& asList() const;
    virtual const FunctionValue& asFunction() const;

    virtual bool operator==(const Value& rhs) const;
    virtual operator bool() const;

    ValuePtr evaluate() const { return shared_from_this(); }

    virtual std::ostream& show(std::ostream& out) const;

    const Type type;

  protected:
    Value(Type type)
        : type(type)
    { }
};

std::ostream& operator<<(std::ostream& out, const Value& value);

} // namespace ast

} // namespace vfn
