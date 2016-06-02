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
    InvalidToken(char next = '\0')
        : Token(Type::Invalid)
        , next(next)
    {}

    bool isValid() const override
    {
        return false;
    }

    std::ostream& show(std::ostream& out) const override
    {
        if (next == '\0') {
            return out;
        } else {
            return out << "[invalid: '" << next << "']";
        }
    }

  private:
    const char next;
};

} // namespace vfn

#endif
