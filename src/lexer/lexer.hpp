// File: lexer.hpp
#ifndef _h_VFN_LEXER_
#define _h_VFN_LEXER_

#include <istream>
#include <memory>
#include <sstream>

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
    char acceptChar();
    void skipWhitespace();
    void skipComment();
    bool checkWordBoundary(char c) const;
    static bool isWordChar(char c);

    void clearToken();

    bool tryComment();
    bool tryInteger();
    bool tryOperator();
    bool tryEqualsSign();
    bool tryKeyword();
    bool tryPattern(const char* keyword);
    bool tryKeywordOrVariable();

    /**
     * An input stream.
     */
    std::istream& in;

    /**
     * The already read part of the current token.
     */
    std::stringstream buffer;

    /**
     * The last token read.
     */
    std::unique_ptr<Token> token;

    /**
     * Number of the tokens already read.
     */
    unsigned int tokenCounter;

    /**
     * The first character of the next token.
     */
    char nextChar;
};

} // namespace vfn

#endif
