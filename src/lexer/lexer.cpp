// File: lexer.cpp

#include "lexer.hpp"

namespace vfn {

/**
 * Create a new @p Lexer instance reading on @p stream.
 *
 * @param stream The used input stream.
 */
Lexer::Lexer(std::istream& stream)
    : in(stream)
    , tokenCounter(0)
{
    clearToken();
}

/**
 * Read a single char.
 *
 * The character is read from the input stream or from the buffer of
 * previously read chars, if @p rewind was called. In the first case,
 * the character is stored in that buffer.
 *
 * @return The newly read character.
 */
int Lexer::readChar()
{
    if (*buf_ptr != '\0') {
        return *buf_ptr++;
    } else {
        char c = in.get();
        if (in.good()) {
            buffer += c;
            buf_ptr = &buffer.back() + 1;
            return buffer.back();
        } else {
            return -1;
        }
    }
}

/**
 * Return the last read character back into the input stream. Remove
 * this character from the read buffer too.
 */
void Lexer::unreadChar()
{
    if (in.good()) {
        in.unget();
        buffer.pop_back();
        buf_ptr = &buffer.back() + 1;
    }
}

/**
 * Skip to the next non-whitespace character in the input stream.
 *
 * @note It does not consider the buffer. It always operates on the
 * input stream.
 */
void Lexer::skipWhitespace()
{
    while (in && std::isspace(in.peek())) {
        in.get();
    }
}

/**
 * Skip until the newline, which ends the comment.
 */
void Lexer::skipComment()
{
    while (in && in.get() != '\n') { }
}

/**
 * Try to read a comment. The comment is then ignored.
 *
 * @return Whether the operation was successful.
 */
bool Lexer::tryComment()
{
    if (readChar() == '#') {
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
    char c = readChar();
    if (c >= '1' && c <= '9') {
        while ((c = readChar()) && c >= '0' && c <= '9') { }
        unreadChar();
        token.reset(new NumberToken(buffer));
        return true;
    } else {
        // Zero cannot be followed by any other digits.
        if (c == '0') {
            c = in.peek();
            if (!(c >= '0' && c <= '9')) {
                token.reset(new NumberToken(buffer));
                return true;
            }
        }
    }

    return false;
}

/**
 * Try to read a keyword.
 *
 * @param keyword A keyword pattern to read.
 * @return Whether the operation was successful.
 */
bool Lexer::tryKeyword(const char* keyword)
{
    // TODO: not implemented
    return false;
}

bool Lexer::tryVariable()
{
    // TODO: not implemented
    return false;
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
    rewind();
}

/**
 * Reset the token buffer iterator.
 *
 * @return The new value of the buffer iterator.
 */
const char* Lexer::rewind()
{
    return buf_ptr = buffer.c_str();
}

/**
 * Read the next token. Discard the current one.
 *
 * @return Reference to the new token.
 */
Token& Lexer::readToken()
{
    do {
        clearToken();
        skipWhitespace();
    } while (tryComment());

    rewind();

    tryInteger();

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
