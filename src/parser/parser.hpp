// File: parser.hpp
#pragma once

#include <exception>
#include <memory>
#include <string>

#include "../lexer/lexer.hpp"
#include "ast/Node.hpp"

namespace vfn {

class unexpected_token : public std::exception
{
  public:
    unexpected_token(const char* msg)
        : message(msg)
    { }

    unexpected_token()
        : message("Unexpected token")
    { }

    const char* what() const noexcept override
    {
        return message;
    }

  private:
    const char* message;
};

class Parser
{
  public:
    using NodePtr = std::unique_ptr<ast::Node>;
    using TokenPtr = std::unique_ptr<Token>;

    Parser(std::unique_ptr<Lexer> lexer);

    NodePtr parse();

  private:
    NodePtr readLine();
    NodePtr readLines();
    NodePtr readBlock();
    NodePtr readAssignOrCall(const std::string& varname);
    NodePtr readExpression();

    TokenPtr checkToken(TokenType expected);
    TokenPtr checkKeyword(Keyword expected);
    TokenPtr requireToken(TokenType expected);
    TokenPtr requireKeyword(Keyword expected);

    Token& getToken();
    Token& advance();

    std::unique_ptr<Lexer> lexer;
};

} // namespace vfn
