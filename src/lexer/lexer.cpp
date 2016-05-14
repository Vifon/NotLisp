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
    rewind();

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
    rewind();

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
 * Try to read all the available a keyword types.
 *
 * @return Whether the operation was successful.
 */
bool Lexer::tryKeyword()
{
    return tryKeyword("(")
        || tryKeyword(")")
        || tryKeyword("[")
        || tryKeyword("]")
        || tryKeyword("{")
        || tryKeyword("}")
        || tryKeyword("if")
        || tryKeyword("else")
        || tryKeyword("let")
        || tryKeyword("fun")
        || tryKeyword("for")
        || tryKeyword("in")
        || tryKeyword("return")
        || tryKeyword("+")
        || tryKeyword("-")
        || tryKeyword("*")
        || tryKeyword("/")
        || tryKeyword("==") // The order of '==' and '=' is important!
        || tryKeyword("=")
        || tryKeyword("!=")
        || tryKeyword(",")
        || tryKeyword(";");
}

/**
 * Try to read a keyword.
 *
 * @param keyword A keyword pattern to read.
 * @return Whether the operation was successful.
 */
bool Lexer::tryKeyword(const char* keyword)
{
    rewind();

    char c = '\0';

    while (*keyword != '\0') {
        if ((c = readChar()) != *keyword++) {
            unreadChar();
            return false;
        }
    }

    if (checkWordBoundary(c)) {
        try {
            token.reset(new KeywordToken(buffer));
        } catch (std::out_of_range& e) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

/**
 * Try to read a variable name.
 *
 * @return Whether the operation was successful.
 */
bool Lexer::tryVariable()
{
    rewind();

    char c = readChar();

    // The first character should =~ /[a-zA-Z]/.
    if (!std::isalpha(c)) {
        return false;
    }

    while (isWordChar(c = readChar())) { }
    unreadChar();

    token.reset(new VarToken(buffer));
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
    return !(isWordChar(c) && isWordChar(in.peek()));
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

    tryInteger()
        || tryKeyword()
        || tryVariable();

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
