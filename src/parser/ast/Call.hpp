// File: Call.hpp
#pragma once

#include "Node.hpp"

#include <memory>

namespace vfn {

namespace ast {

class Call : public Node
{
  public:
    Call(const std::string& function, std::unique_ptr<Node>&& args)
        : function_name(function)
        , arguments_tuple(std::move(args))
    {}

    ResultPtr evaluate() const override
    {
        // TODO
        std::cout << "Calling " << function_name << std::endl;
        return ResultPtr{new VoidResult};
    }

  private:
    const std::string function_name;
    std::unique_ptr<Node> arguments_tuple;
};

} // namespace ast

} // namespace vfn