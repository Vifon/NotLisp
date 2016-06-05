// File: Block.hpp
#pragma once

#include <map>
#include <stdexcept>
#include <vector>

#include "Node.hpp"
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

        for (auto& subtree : subtrees) {
            ret = subtree->evaluate();
        }

        return ret;
    }

  protected:
    ValuePtr& lookup(const std::string& varname) override
    {
        if (scope.count(varname)) {
            return scope[varname];
        } else {
            return Node::lookup(varname);
        }
    }

    void addVar(const std::string& varname) override
    {
        if (scope.count(varname)) {
            throw std::runtime_error("Variable already declared: " + varname);
        } else {
            scope[varname] = ValuePtr{new VoidValue};
        }
    }

  private:
    std::vector<NodePtr> subtrees;

    std::map<std::string, ValuePtr> scope;
};

} // namespace ast

} // namespace vfn
