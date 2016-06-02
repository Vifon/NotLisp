// File: Assign.hpp
#pragma once

#include "Node.hpp"

#include <memory>

#include <iostream>             // TODO

namespace vfn {

namespace ast {

class Assign : public Node
{
  public:
    Assign(const std::string& variable, std::unique_ptr<Node>&& value)
        : variable(variable)
        , value(std::move(value))
    {}

    ResultPtr evaluate() const override
    {
        // TODO
        std::cout << "I'm assigning " << value.get() << " to " << variable << std::endl;
        return ResultPtr{new VoidResult};
    }

  private:
    const std::string variable;
    std::unique_ptr<Node> value;
};

} // namespace ast

} // namespace vfn