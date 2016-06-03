// File: parser.cpp

#include "parser.hpp"

#include <vector>

#include "ast/Assign.hpp"
#include "ast/BinaryOperator.hpp"
#include "ast/Block.hpp"
#include "ast/Call.hpp"
#include "ast/Function.hpp"
#include "ast/Return.hpp"
#include "ast/Tuple.hpp"
#include "ast/UnaryOperator.hpp"
#include "ast/Variable.hpp"
#include "ast/Result.hpp"

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
        if (checkKeyword(Keyword::Assignment)) {
            line = readAssign(varname->asVar());
        } else {
            requireKeyword(Keyword::ParenBegin);
            line = readCall(varname->asVar());
        }
    } else if (checkKeyword(Keyword::Let)) {
        line = readDeclaration();
    } else if (checkKeyword(Keyword::Return)) {
        NodePtr value = readExpression();
        line.reset(new ast::Return{std::move(value)});
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

Parser::NodePtr Parser::readAssign(const std::string& varname)
{
    NodePtr value = readExpression();
    NodePtr assignment{new ast::Assign{varname, std::move(value)}};
    return assignment;
}

Parser::NodePtr Parser::readCall(const std::string& varname)
{
    NodePtr tuple = readTuple();
    requireKeyword(Keyword::ParenEnd);
    NodePtr call{new ast::Call{varname, std::move(tuple)}};
    return call;
}

// TODO: higher order function
Parser::NodePtr Parser::readExpression()
{
    NodePtr lhs = readSum();
    if (checkKeyword(Keyword::Equals) || checkKeyword(Keyword::NotEquals)) {
        Keyword op = getToken().asKeyword();
        NodePtr rhs = readSum();
        NodePtr binary{new ast::BinaryOperator{op, std::move(lhs), std::move(rhs)}};
        return binary;
    } else {
        return lhs;
    }
}

Parser::NodePtr Parser::readSum()
{
    NodePtr lhs = readMult();
    if (checkKeyword(Keyword::Plus) || checkKeyword(Keyword::Minus)) {
        Keyword op = getToken().asKeyword();
        NodePtr rhs = readMult();
        NodePtr binary{new ast::BinaryOperator{op, std::move(lhs), std::move(rhs)}};
        return binary;
    } else {
        return lhs;
    }
}

Parser::NodePtr Parser::readMult()
{
    NodePtr lhs = readValue();
    if (checkKeyword(Keyword::Mult) || checkKeyword(Keyword::Div)) {
        Keyword op = getToken().asKeyword();
        NodePtr rhs = readValue();
        NodePtr binary{new ast::BinaryOperator{op, std::move(lhs), std::move(rhs)}};
        return binary;
    } else {
        return lhs;
    }
}

Parser::NodePtr Parser::readValue()
{
    if (TokenPtr varname = checkToken(Token::Type::Var)) {
        if (checkKeyword(Keyword::ParenBegin)) {
            return readCall(varname->asVar());
        } else {
            NodePtr var{new ast::Variable{varname->asVar()}};
            return var;
        }
    } else if (checkKeyword(Keyword::ParenBegin)) {
        NodePtr expr = readExpression();
        requireKeyword(Keyword::ParenEnd);
        return expr;
    } else if (checkKeyword(Keyword::Minus)) {
        NodePtr expr = readExpression();
        NodePtr unary{new ast::UnaryOperator{Keyword::Minus, std::move(expr)}};
        return expr;
    } else {
        return readLiteral();
    }
}

Parser::NodePtr Parser::readLiteral()
{
    if (TokenPtr num = checkToken(Token::Type::Number)) {
        NodePtr literal{new ast::NumberResult{static_cast<signed int>(num->asInt())}};
        return literal;
    } else if (checkKeyword(Keyword::ListBegin)) {
        NodePtr list = readTuple();
        requireKeyword(Keyword::ListEnd);
        return list;
    } else {
        return readFunction();
    }
}

Parser::NodePtr Parser::readFunction()
{
    requireKeyword(Keyword::Fun);
    requireKeyword(Keyword::ParenBegin);
    NodePtr args = readTuple();  // TODO: VarTuple
    requireKeyword(Keyword::ParenEnd);
    NodePtr body = readBlock();

    NodePtr function{new ast::Function{std::move(args), std::move(body)}};
    return function;
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
        throw unexpected_input(getToken());
    }
}

Parser::TokenPtr Parser::requireKeyword(Keyword expected)
{
    TokenPtr token = checkKeyword(expected);
    if (token) {
        return token;
    } else {
        throw unexpected_input(getToken());
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
