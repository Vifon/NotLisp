// File: lexer.cpp

#include "lexer.hpp"

#include "tokens/invalid_token.hpp"
#include "tokens/keyword_token.hpp"
#include "tokens/number_token.hpp"
#include "tokens/var_token.hpp"

namespace vfn {

/**
 * Create a new @p Lexer instance reading on @p stream.
 *
 * @param stream The used input stream.
 */
Lexer::Lexer(std::istream& stream)
    : in(stream)
    , tokenCounter(0)
    , nextChar(in.get())
{
    clearToken();
}

/**
 * Accept @p nextChar into @p buffer and extract the next character
 * from the stream.
 *
 * @return The next character from the stream.
 */
char Lexer::acceptChar()
{
    buffer.put(nextChar);
    return nextChar = in.get();
}

/**
 * Skip to the next non-whitespace character in the input stream.
 */
void Lexer::skipWhitespace()
{
    while (in && std::isspace(nextChar)) {
        nextChar = in.get();
    }
}

/**
 * Skip until the newline, which ends the comment.
 */
void Lexer::skipComment()
{
    while (in && in.get() != '\n') { }
    nextChar = in.get();
}

/**
 * Try to read a comment. The comment is then ignored.
 *
 * @return Whether the operation was successful.
 */
bool Lexer::tryComment()
{
    if (nextChar == '#') {
        skipComment();
        return true;
    } else {
        return false;
    }
}

/**
 * Try to read an integer.
 *
 * @return Whether the operation was successful.
 */
bool Lexer::tryInteger()
{
    if (nextChar >= '1' && nextChar <= '9') {
        while (acceptChar() >= '0' && nextChar <= '9') { }
        token.reset(new NumberToken(buffer.str()));
        return true;
    } else {
        // Zero cannot be followed by any other digits.
        if (nextChar == '0') {
            if (!(acceptChar() >= '0' && nextChar <= '9')) {
                token.reset(new NumberToken(buffer.str()));
                return true;
            }
        }
    }

    return false;
}

/**
 * Try to read an operator.
 *
 * @return Whether the operation was successful.
 */
bool Lexer::tryOperator()
{
    return tryPattern("(")
        || tryPattern(")")
        || tryPattern("[")
        || tryPattern("]")
        || tryPattern("{")
        || tryPattern("}")
        || tryPattern("+")
        || tryPattern("-")
        || tryPattern("*")
        || tryPattern("/")
        || tryPattern("!=")
        || tryPattern(",")
        || tryPattern(";")
        || tryEqualsSign();
}

/**
 * Try to read either "==" or "=".
 */
bool Lexer::tryEqualsSign()
{
    if (nextChar == '=') {
        if (acceptChar() == '=') {
            acceptChar();
        }

        try {
            token.reset(new KeywordToken(buffer.str()));
            return true;
        } catch (std::out_of_range& e) {
            return false;
        }
    } else {
        return false;
    }
}

/**
 * Try to read a specific pattern.
 *
 * @param pattern A pattern to read.
 * @return Whether the operation was successful.
 *
 * @note The consumed characters are not returned to the stream. Make
 * sure the pattern will be known to fail or not peeking just one
 * character ahead.
 */
bool Lexer::tryPattern(const char* pattern)
{
    while (*pattern != '\0') {
        if (nextChar != *pattern++) {
            return false;
        } else {
            acceptChar();
        }
    }

    if (checkWordBoundary(nextChar)) {
        try {
            token.reset(new KeywordToken(buffer.str()));
        } catch (std::out_of_range& e) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

/**
 * Try to read a keyword or a variable name.
 *
 * @return Whether the operation was successful.
 */
bool Lexer::tryKeywordOrVariable()
{
    // The first character should =~ /[a-zA-Z]/.
    if (!std::isalpha(nextChar)) {
        return false;
    }

    while (isWordChar(acceptChar())) { }

    try {
        token.reset(new KeywordToken(buffer.str()));
    } catch (std::out_of_range& e) {
        token.reset(new VarToken(buffer.str()));
    }

    return true;
}

/**
 * Check if the character is alphanumeric or an underscore.
 */
bool Lexer::isWordChar(char c)
{
    return (std::isalnum(c) || c == '_');
}

/**
 * Check if either the given character or the next one is a non-word
 * character.
 */
bool Lexer::checkWordBoundary(char c) const
{
    return !(isWordChar(buffer.str().back()) && isWordChar(nextChar));
}

/**
 * Reset the current token data.
 *
 * This includes the token buffer and the pointer used to iterate it.
 */
void Lexer::clearToken()
{
    token.reset(new InvalidToken);
    buffer.clear();
    buffer.str(std::string());
}

/**
 * Read the next token. Discard the current one.
 *
 * After it returns an invalid token, the behavior of further calls is
 * undefined.
 *
 * @return Reference to the new token.
 */
Token& Lexer::readToken()
{
    do {
        clearToken();
        skipWhitespace();
    } while (tryComment());

    tryInteger()
        || tryOperator()
        || tryKeywordOrVariable();

    if (token->isValid()) {
        ++tokenCounter;
    }

    return getToken();
}

/**
 * @return A reference to the last read token.
 */
Token& Lexer::getToken()
{
    return *token;
}

} // namespace vfn
