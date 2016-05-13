// File: tokens.hpp
#ifndef _h_VFN_TOKENS_
#define _h_VFN_TOKENS_

#include <sstream>

namespace vfn {

/**
 * A generic abstract Token.
 */
class Token
{
  public:
    virtual ~Token() { };
  protected:
    Token() { }
};

/**
 * A numerical constant.
 */
class NumberToken : public Token
{
  public:
    /**
     * Parse the buffer and store the numerical value.
     */
    NumberToken(const char* buf)
    {
        std::stringstream ss;
        ss << buf;
        ss >> value;
    }

    /**
     * @return The numerical value of this token.
     */
    unsigned int getValue() const
    {
        return value;
    }

  private:
    /**
     * Numerical value of this token.
     */
    unsigned int value;
};

/**
 * A token rejected by the lexer.
 */
class InvalidToken : public Token
{ };

} // namespace vfn

#endif
