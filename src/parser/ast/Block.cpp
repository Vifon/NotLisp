// File: Block.cpp

#include "Block.hpp"

#include "Void.hpp"

namespace vfn {

namespace ast {

ValuePtr Block::evaluate(Scope& scope) const
{
    ValuePtr ret = Value::make<Void>();

    Scope new_scope{scope};

    for (auto& subtree : subtrees) {
        ret = subtree->evaluate(new_scope);
    }

    return ret;
}

} // namespace ast

} // namespace vfn
