// File: lexer.cpp

#include "lexer.hpp"

namespace vfn {

Lexer::Lexer(std::istream& stream)
    : in(stream)
    , buffer()
    , buf_ptr(buffer.c_str())
    , token()
{
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
char Lexer::readChar()
{
    if (*buf_ptr) {
        return *buf_ptr++;
    } else {
        buffer += in.get();
        buf_ptr = &buffer.back() + 1;
        return buffer.back();
    }
}

/**
 * Skip to the next non-whitespace character in the input stream.
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
 * Try to read an integer.
 *
 * @return Whether the operation was successful.
 */
bool Lexer::tryInteger()
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
    clearToken();
    skipWhitespace();
    readChar();

    switch (buffer.back()) {
    case '#':
        skipComment();
        return readToken();
    case 'a' ... 'z':
        skipComment();
    }

    token.reset(new InvalidToken);

    return getToken();
}

} // namespace vfn
