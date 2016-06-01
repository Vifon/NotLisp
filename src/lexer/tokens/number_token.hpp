// File: number_token.hpp
#ifndef _h_VFN_NUMBER_TOKEN_
#define _h_VFN_NUMBER_TOKEN_

#include <ostream>
#include <sstream>
#include <string>

#include "token.hpp"

namespace vfn {

/**
 * A numerical constant.
 */
class NumberToken : public Token
{
  public:
    /**
     * Parse the buffer and store the numerical value.
     */
    NumberToken(const std::string& buf)
        : Token(TokenType::Number)
    {
        std::stringstream ss;
        ss << buf;
        ss >> value;
    }

    unsigned int asInt() const override
    {
        return value;
    }

    bool operator==(unsigned int n) const override
    {
        return asInt() == n;
    }

    Token* clone() const override
    {
        return new NumberToken(*this);
    }

    std::ostream& show(std::ostream& out) const override
    {
        return out << "[num: " << asInt() << "]";
    }

  private:
    /**
     * Numerical value of this token.
     */
    unsigned int value;
};

} // namespace vfn

#endif
