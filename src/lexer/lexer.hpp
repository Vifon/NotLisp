// File: lexer.hpp
#ifndef _h_VFN_LEXER_
#define _h_VFN_LEXER_

#include <istream>
#include <memory>
#include <string>

#include "tokens/token.hpp"

namespace vfn {

/**
 * Responsible for breaking down the input stream into the stream of
 * tokens.
 */
class Lexer
{
  public:
    Lexer(std::istream& stream);

    Token& readToken();
    Token& getToken();

    unsigned int tokensRead() const { return tokenCounter; }

  private:
    int readChar();
    void unreadChar();
    void skipWhitespace();
    void skipComment();
    bool checkWordBoundary(char c) const;
    static bool isWordChar(char c);

    void clearToken();
    const char* rewind();

    bool tryComment();
    bool tryInteger();
    bool tryKeyword();
    bool tryKeyword(const char* keyword);
    bool tryVariable();

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

    /**
     * Number of the tokens already read.
     */
    unsigned int tokenCounter;
};

} // namespace vfn

#endif
