// File: parser.cpp

#include "parser.hpp"

#include <vector>

#include "ast/Assign.hpp"
#include "ast/Block.hpp"

namespace vfn {

Parser::Parser(std::unique_ptr<Lexer> lexer)
    : lexer(std::move(lexer))
{}

Parser::NodePtr Parser::parse()
{
    advance();
    return readLines();
}

Parser::NodePtr Parser::readBlock()
{
    if (checkKeyword(Keyword::BlockBegin)) {
        NodePtr lines = readLines();
        requireKeyword(Keyword::BlockEnd);
        return lines;
    } else {
        return readLine();
    }
}

Parser::NodePtr Parser::readLine()
{
    NodePtr line;
    if (TokenPtr varname = checkToken(TokenType::Var)) {
        line = readAssignOrCall(varname->asVar());
    } else {
        // TODO
        return nullptr;
    }

    requireKeyword(Keyword::Semicolon);
    return line;
}

Parser::NodePtr Parser::readLines()
{
    std::vector<NodePtr> subtrees;
    NodePtr line;
    while ((line = readLine()) != nullptr) {
        subtrees.push_back(std::move(line));
    }
    NodePtr block{new ast::Block{std::move(subtrees)}};
    return block;
}

Parser::NodePtr Parser::readAssignOrCall(const std::string& varname)
{
    if (checkKeyword(Keyword::Assignment)) {
        NodePtr value = readExpression();
        NodePtr assignment{new ast::Assign{varname, std::move(value)}};
        return assignment;
    } else if (checkKeyword(Keyword::ParenBegin)) {
        // TODO
        throw unexpected_token();
    } else {
        throw unexpected_token();
    }
}

Parser::NodePtr Parser::readExpression()
{
    // TODO
    advance();
    return nullptr;
}

Parser::TokenPtr Parser::checkToken(TokenType expected)
{
    TokenPtr token{getToken().clone()};

    if (token->type != expected) {
        return nullptr;
    } else {
        advance();
        return token;
    }
}

Parser::TokenPtr Parser::checkKeyword(Keyword expected)
{
    TokenPtr token{getToken().clone()};

    if (token->type != TokenType::Keyword || token->asKeyword() != expected) {
        return nullptr;
    } else {
        advance();
        return token;
    }
}

Parser::TokenPtr Parser::requireToken(TokenType expected)
{
    TokenPtr token = checkToken(expected);
    if (token) {
        return token;
    } else {
        throw unexpected_token();
    }
}

Parser::TokenPtr Parser::requireKeyword(Keyword expected)
{
    TokenPtr token = checkKeyword(expected);
    if (token) {
        return token;
    } else {
        throw unexpected_token();
    }
}

Token& Parser::getToken()
{
    return lexer->getToken();
}

Token& Parser::advance()
{
    return lexer->readToken();
}

} // namespace vfn
