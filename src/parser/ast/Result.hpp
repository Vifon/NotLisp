// File: Result.hpp
#pragma once

#include <vector>

#include "bad_result_cast.hpp"
#include "Node.hpp"

namespace vfn {

namespace ast {

class Result : public Node
{
  public:
    enum class Type {
        Function,
        Int,
        List,
        Void,
    };

    virtual ~Result() { }

    virtual int asInt() const
    {
        throw bad_result_cast("Not an integer");
    }

    virtual const std::vector<ResultPtr>& asList() const
    {
        throw bad_result_cast("Not a list");
    }

    virtual bool operator==(const Result& rhs) const
    {
        return type == rhs.type;
    }

    const Type type;

  protected:
    Result(Type type)
        : type(type)
    { }
};

class VoidResult : public Result
{
  public:
    VoidResult()
        : Result(Result::Type::Void)
    { }

    ResultPtr evaluate() const override
    {
        return ResultPtr{new VoidResult{*this}};
    }
};

class NumberResult : public Result
{
  public:
    NumberResult(int n)
        : Result(Result::Type::Int)
        , value(n)
    { }

    int asInt() const override
    {
        return value;
    }

    bool operator==(const Result& rhs) const override
    {
        return Result::operator==(rhs) && asInt() == rhs.asInt();
    }

    ResultPtr evaluate() const override
    {
        return ResultPtr{new NumberResult{*this}};
    }

  private:
    int value;
};

class ListResult : public Result
{
  public:
    ListResult(std::vector<ResultPtr>&& list)
        : Result(Result::Type::List)
        , list(std::move(list))
    { }

    const std::vector<ResultPtr>& asList() const override
    {
        return list;
    }

    bool operator==(const Result& rhs) const override
    {
        return Result::operator==(rhs) && asList() == rhs.asList();
    }

    ResultPtr evaluate() const override
    {
        // TODO: shared_ptr?
        // return ResultPtr{new ListResult{*this}};
    }

  private:
    std::vector<ResultPtr> list;
};

} // namespace ast

} // namespace vfn
