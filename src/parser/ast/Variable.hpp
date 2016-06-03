// File: Variable.hpp
#pragma once

#include "Node.hpp"

#include <memory>

namespace vfn {

namespace ast {

class Variable : public Node
{
  public:
    Variable(const std::string& varname)
        : name(varname)
    {}

    ResultPtr evaluate() const override
    {
        // TODO
        return ResultPtr{new VoidResult};
    }

  private:
    const std::string name;
};

} // namespace ast

} // namespace vfn
