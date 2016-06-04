// File: parser.hpp
#pragma once

#include <exception>
#include <initializer_list>
#include <memory>
#include <string>

#include "../lexer/lexer.hpp"
#include "ast/Node.hpp"

namespace vfn {

class unexpected_input : public std::exception
{
  public:
    unexpected_input(const Token& token)
        : message("Unexpected token: ")
    {
        std::stringstream ss;
        ss << token;
        message += ss.str();
    }

    unexpected_input()
        : message("Unexpected token")
    { }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

  private:
    std::string message;
};

class Parser
{
  public:
    using NodePtr = ast::NodePtr;
    using TokenPtr = std::unique_ptr<Token>;

    Parser(std::unique_ptr<Lexer> lexer);

    NodePtr parse();

  private:
    NodePtr readLine();
    NodePtr readLines();
    NodePtr readBlock();
    NodePtr readDeclaration();
    NodePtr readCall(const std::string& varname);
    NodePtr readCond();
    NodePtr readLoop();
    NodePtr readMap();
    NodePtr readFilter();
    NodePtr readExpression();
    NodePtr readOperator(
        NodePtr (Parser::*readNextExpression)(),
        const std::initializer_list<Keyword>& operators);
    NodePtr readComparison();
    NodePtr readSum();
    NodePtr readMult();
    NodePtr readValue();
    NodePtr readLiteral();
    NodePtr readFunction();
    NodePtr readTuple();
    NodePtr readVarTuple();

    TokenPtr checkToken(Token::Type expected);
    TokenPtr checkKeyword(Keyword expected);
    TokenPtr checkKeywords(const std::initializer_list<Keyword>& expected);
    TokenPtr requireToken(Token::Type expected);
    TokenPtr requireKeyword(Keyword expected);

    Token& getToken();
    Token& advance();

    std::unique_ptr<Lexer> lexer;
};

} // namespace vfn
