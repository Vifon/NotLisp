// File: parser.hpp
#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "../lexer/lexer.hpp"
#include "ast/Node.hpp"

namespace vfn {

class Parser
{
  public:
    using NodePtr = ast::NodePtr;
    using TokenPtr = std::unique_ptr<Token>;

    Parser(std::unique_ptr<Lexer> lexer);

    NodePtr parse();

  private:
    NodePtr readLine(bool is_toplevel = false);
    NodePtr readLines(bool is_toplevel = false);
    NodePtr readBlockOrLine(bool is_toplevel = false);
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
    std::vector<std::string> readVarTuple();

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
