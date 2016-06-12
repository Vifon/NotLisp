// File: Node.hpp
#pragma once

#include <memory>

#include "Scope.hpp"
#include "Value.hpp"

namespace vfn {

namespace ast {

class Node;
using NodePtr = std::unique_ptr<const Node>;

class Node
{
  public:
    virtual ~Node() { }

    virtual ValuePtr evaluate(Scope& scope) const = 0;

    template <typename T, typename ...Args>
    static NodePtr make(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    ValuePtr run() const;

  protected:
    Node() { }
};

} // namespace ast

} // namespace vfn
