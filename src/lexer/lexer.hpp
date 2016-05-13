// File: lexer.hpp
#ifndef _h_VFN_LEXER_
#define _h_VFN_LEXER_

#include <istream>
#include <memory>
#include <string>

#include "tokens.hpp"

namespace vfn {

/**
 * Responsible for breaking down the input stream into the stream of
 * tokens.
 */
class Lexer
{
  public:
    /**
     * Create a new @p Lexer instance reading on @p stream.
     *
     * @param stream The used input stream.
     */
    Lexer(std::istream& stream);

    Token& readToken();

    /**
     * @return A reference to the last read token.
     */
    Token& getToken() { return *token; }

  private:
    char readChar();
    void skipWhitespace();
    void skipComment();

    void clearToken();
    const char* rewind();

    bool tryInteger();

    /**
     * An input stream.
     */
    std::istream& in;

    /**
     * The already read part of the current token.
     */
    std::string buffer;

    /**
     * The currently considered character of the current token.
     *
     * If points to <tt>'\0'</tt>, the new character will be read and
     * appended to the buffer.
     */
    const char* buf_ptr;

    /**
     * The last token read.
     */
    std::unique_ptr<Token> token;
};

} // namespace vfn

#endif
