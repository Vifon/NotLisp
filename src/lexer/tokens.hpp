/**
 * @file tokens.hpp
 */
#ifndef _h_VFN_TOKENS_
#define _h_VFN_TOKENS_

#include <exception>
#include <sstream>
#include <map>

namespace vfn {

/**
 * Available symbolic constants.
 */
enum class Keyword {
    // Braces
    ParenBegin,                 ///< <tt>'('</tt>
    ParenEnd,                   ///< <tt>')'</tt>
    ListBegin,                  ///< <tt>'['</tt>
    ListEnd,                    ///< <tt>']'</tt>
    BlockBegin,                 ///< <tt>'{'</tt>
    BlockEnd,                   ///< <tt>'}'</tt>

    // Keywords
    If,                         ///< <tt>if</tt>
    Else,                       ///< <tt>else</tt>
    Let,                        ///< <tt>let</tt>
    Fun,                        ///< <tt>fun</tt>
    For,                        ///< <tt>for</tt>
    In,                         ///< <tt>in</tt>
    Return,                     ///< <tt>return</tt>

    // Operators
    Plus,                       ///< <tt>'+'</tt>
    Minus,                      ///< <tt>'-'</tt>
    Mult,                       ///< <tt>'*'</tt>
    Div,                        ///< <tt>'/'</tt>
    Assignment,                 ///< <tt>'='</tt>
    Equals,                     ///< <tt>'=='</tt>
    NotEquals,                  ///< <tt>'!='</tt>

    // Separators
    Comma,                      ///< <tt>','</tt>
    Semicolon,                  ///< <tt>';'</tt>
};

class bad_token_cast : public std::exception
{
  public:
    bad_token_cast(const char* msg)
        : message(msg)
    { }

    bad_token_cast()
        : message("")
    { }

    const char* what() const noexcept override
    {
        return message;
    }

  private:
    const char* message;
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
    NumberToken(const std::string& buf)
    {
        std::stringstream ss;
        ss << buf;
        ss >> value;
    }

    unsigned int asInt() const override
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
 * A keyword token with discrete values.
 */
class KeywordToken : public Token
{
  public:
    KeywordToken(Keyword s)
        : keyword(s)
    { }

    KeywordToken(const std::string& s)
        : keyword(mapping.at(s))
    { }

    Keyword asKeyword() const override
    {
        return keyword;
    }

    /**
     * The represented keyword.
     */
    const Keyword keyword;

  private:
    static const std::map<std::string, Keyword> mapping;
};

/**
 * A variable with a name.
 */
class VarToken : public Token
{
  public:
    VarToken(const std::string& buf)
        : name(buf)
    { }

    const std::string& asVar() const override
    {
        return name;
    }

    /**
     * The name of the represented variable.
     */
    const std::string name;
};

/**
 * A token rejected by the lexer.
 */
class InvalidToken : public Token
{
  public:
    bool isValid() const override
    {
        return false;
    }
};

} // namespace vfn

#endif
