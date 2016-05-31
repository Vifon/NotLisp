// File: token.hpp
#ifndef _h_VFN_TOKEN_
#define _h_VFN_TOKEN_

#include <ostream>
#include <string>

#include "bad_token_cast.hpp"
#include "keyword.hpp"

namespace vfn {

/**
 * A tag used to distinguish various token types without using RTTI.
 */
enum class TokenType {
    Keyword,
    Number,
    Var,
    Invalid,
};

/**
 * A generic abstract Token.
 */
class Token
{
  public:
    /**
     * Whether the token is valid. Overriden in the @p InvalidToken
     * subclass.
     */
    virtual bool isValid() const
    {
        return true;
    }

    /**
     * Try to get the numerical value of this token.
     */
    virtual unsigned int asInt() const
    {
        throw bad_token_cast("Not an integer");
    }

    /**
     * Try to get the keyword associated with this token.
     */
    virtual Keyword asKeyword() const
    {
        throw bad_token_cast("Not a keyword");
    }

    /**
     * Try to get the name of the variable represented by this token.
     */
    virtual const std::string& asVar() const
    {
        throw bad_token_cast("Not a variable");
    }

    virtual ~Token() { };

    /**
     * Compare a numeric constant with a number.
     */
    virtual bool operator==(unsigned int n) const { return false; }

    /**
     * Compare a variable with a string.
     */
    virtual bool operator==(const std::string& str) const { return false; }

    /**
     * Compare a keyword with a keyword symbol.
     */
    virtual bool operator==(Keyword keyword) const { return false; }

    /**
     * Print a token to a stream.
     */
    virtual std::ostream& show(std::ostream& out) const
    {
        throw bad_token_cast("Not showable");
    }

    /**
     * An enum used to easily switch over various token types.
     *
     * @note Must be set by the derived type's ctor!
     */
    const TokenType type;

  protected:
    Token(TokenType type)
        : type(type)
    { }
};

std::ostream& operator<<(std::ostream& out, const Token& token);

} // namespace vfn

#endif
