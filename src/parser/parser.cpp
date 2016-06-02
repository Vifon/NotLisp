// File: parser.cpp

#include "parser.hpp"

#include <vector>

#include "ast/Assign.hpp"
#include "ast/Block.hpp"
#include "ast/Call.hpp"
#include "ast/Tuple.hpp"

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

    if (lexer->eof()) {
        return nullptr;
    }

    if (TokenPtr varname = checkToken(Token::Type::Var)) {
        line = readAssignOrCall(varname->asVar());
    } else if (checkKeyword(Keyword::Let)) {
        line = readDeclaration();
    } else {
        // TODO
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

Parser::NodePtr Parser::readDeclaration()
{
    TokenPtr varname = requireToken(Token::Type::Var);
    requireKeyword(Keyword::Assignment);
    NodePtr value = readExpression();
    NodePtr assignment{new ast::Assign{varname->asVar(), std::move(value)}};
    // NodePtr declaration{new ast::Declaration{std::move(assignment)}};
    // return declaration;
    return assignment;      // TODO
}

Parser::NodePtr Parser::readAssignOrCall(const std::string& varname)
{
    if (checkKeyword(Keyword::Assignment)) {
        NodePtr value = readExpression();
        NodePtr assignment{new ast::Assign{varname, std::move(value)}};
        return assignment;
    } else if (checkKeyword(Keyword::ParenBegin)) {
        NodePtr tuple = readTuple();
        requireKeyword(Keyword::ParenEnd);
        NodePtr call{new ast::Call{varname, std::move(tuple)}};
        return call;
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

Parser::NodePtr Parser::readTuple()
{
    std::vector<NodePtr> expressions;

    // TODO: empty tuple?
    do {
        NodePtr expr = readExpression();
        expressions.push_back(std::move(expr));
    } while (checkKeyword(Keyword::Comma));

    NodePtr tuple{new ast::Tuple{std::move(expressions)}};
    return tuple;
}

Parser::TokenPtr Parser::checkToken(Token::Type expected)
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

    if (token->type != Token::Type::Keyword || token->asKeyword() != expected) {
        return nullptr;
    } else {
        advance();
        return token;
    }
}

Parser::TokenPtr Parser::requireToken(Token::Type expected)
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
