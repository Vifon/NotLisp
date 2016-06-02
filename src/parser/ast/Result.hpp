// File: Result.hpp
#pragma once

#include <memory>
#include <vector>

#include "bad_result_cast.hpp"

namespace vfn {

namespace ast {

class Result;
using ResultPtr = std::unique_ptr<Result>;

class Result
{
  public:
    enum class Type {
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

  private:
    std::vector<ResultPtr> list;
};

} // namespace ast

} // namespace vfn
