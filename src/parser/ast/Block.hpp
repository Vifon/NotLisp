// File: Block.hpp
#pragma once

#include <map>
#include <stdexcept>
#include <vector>

#include "Node.hpp"
#include "Return.hpp"
#include "VoidValue.hpp"

namespace vfn {

namespace ast {

class Block : public Node
{
  public:
    Block(std::vector<NodePtr>&& subtrees)
        : subtrees(std::move(subtrees))
    {
        for (auto& node : this->subtrees) {
            node->parent = this;
        }
    }

    Block() { }

    ValuePtr evaluate() override
    {
        ValuePtr ret{new VoidValue};;

        try {
            for (auto& subtree : subtrees) {
                ret = subtree->evaluate();
            }

            scope.clear();

            return ret;
        } catch (Return::UglyHack& early_return) {
            scope.clear();

            if (parent == nullptr) {
                return early_return.return_value;
            } else {
                throw early_return;
            }
        }
    }

    ValuePtr& lookup(const std::string& varname) override
    {
        if (scope.count(varname)) {
            return scope[varname];
        } else {
            return Node::lookup(varname);
        }
    }

    ValuePtr& addVar(const std::string& varname) override
    {
        if (scope.count(varname)) {
            throw std::runtime_error("Variable already declared: " + varname);
        } else {
            return scope[varname] = ValuePtr{new VoidValue};
        }
    }

  private:
    std::vector<NodePtr> subtrees;

    std::map<std::string, ValuePtr> scope;
};

} // namespace ast

} // namespace vfn
