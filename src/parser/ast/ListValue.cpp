// File: ListValue.cpp

#include "ListValue.hpp"

namespace vfn {

namespace ast {

bool ListValue::operator==(const Value& rhs) const
{
    return Value::operator==(rhs) && asList() == rhs.asList();
}

std::ostream& ListValue::show(std::ostream& out) const
{
    if (list.empty()) {
        out << "[]";
    } else {
        auto it = list.begin();
        out << "[" << **it++;
        while (it != list.end()) {
            out << ", " << **it++;
        }
        out << "]";
    }
    return out;
}

} // namespace ast

} // namespace vfn
