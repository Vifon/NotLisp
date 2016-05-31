// File: invalid_token.hpp
#ifndef _h_VFN_INVALID_TOKEN_
#define _h_VFN_INVALID_TOKEN_

#include "token.hpp"

namespace vfn {

/**
 * A token rejected by the lexer.
 */
class InvalidToken : public Token
{
  public:
    InvalidToken()
        : Token(TokenType::Invalid)
    {}

    bool isValid() const override
    {
        return false;
    }
};

} // namespace vfn

#endif
