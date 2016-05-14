// File: var_token.hpp
#ifndef _h_VFN_VAR_TOKEN_
#define _h_VFN_VAR_TOKEN_

#include <ostream>
#include <string>

#include "token.hpp"

namespace vfn {

/**
 * A variable with a name.
 */
class VarToken : public Token
{
  public:
    VarToken(const std::string& buf)
        : name(buf)
    { }

    const std::string& asVar() const override
    {
        return name;
    }

    bool operator==(const std::string& str) const override
    {
        return asVar() == str;
    }

    std::ostream& show(std::ostream& out) const override
    {
        return out << "[var: " << asVar() << "]";
    }

    /**
     * The name of the represented variable.
     */
    const std::string name;
};

} // namespace vfn

#endif
