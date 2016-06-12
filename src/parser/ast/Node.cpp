// File: Node.cpp

#include "Node.hpp"

#include "Return.hpp"
#include "Scope.hpp"

namespace vfn {

namespace ast {

ValuePtr Node::run() const
{
    Scope root_scope;
    try {
        return evaluate(root_scope);
    } catch (const Return::UglyHack& early_return) {
        return early_return.return_value;
    }
}

} // namespace ast

} // namespace vfn
