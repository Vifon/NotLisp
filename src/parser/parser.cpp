// File: parser.cpp

#include "parser.hpp"

#include <vector>

#include "ast/Assign.hpp"
#include "ast/BinaryOperator.hpp"
#include "ast/Block.hpp"
#include "ast/Call.hpp"
#include "ast/Cond.hpp"
#include "ast/Declaration.hpp"
#include "ast/Filter.hpp"
#include "ast/FunctionValue.hpp"
#include "ast/Loop.hpp"
#include "ast/Map.hpp"
#include "ast/Print.hpp"
#include "ast/Return.hpp"
#include "ast/Tuple.hpp"
#include "ast/UnaryOperator.hpp"
#include "ast/Value.hpp"
#include "ast/Variable.hpp"

namespace vfn {

Parser::Parser(std::unique_ptr<Lexer> lexer)
    : lexer(std::move(lexer))
{}

Parser::NodePtr Parser::parse()
{
    advance();
    return readLines(true);
}

Parser::NodePtr Parser::readBlockOrLine(bool is_toplevel)
{
    if (checkKeyword(Keyword::BlockBegin)) {
        return readLines();
    } else {
        return readLine(is_toplevel);
    }
}

Parser::NodePtr Parser::readLine(bool is_toplevel)
{
    NodePtr line;

    if (TokenPtr varname = checkToken(Token::Type::Var)) {
        if (checkKeyword(Keyword::Assignment)) {
            NodePtr value = readExpression();
            line.reset(new ast::Assign{varname->asVar(), std::move(value)});
        } else {
            requireKeyword(Keyword::ParenBegin);
            line = readCall(varname->asVar());
        }
    } else if (checkKeyword(Keyword::Let)) {
        line = readDeclaration();
    } else if (checkKeyword(Keyword::Return)) {
        if (checkKeyword(Keyword::Semicolon)) {
            return NodePtr{new ast::Return};
        } else {
            NodePtr value = readExpression();
            line.reset(new ast::Return{std::move(value)});
        }
    } else if (checkKeyword(Keyword::Print)) {
        requireKeyword(Keyword::ParenBegin);
        NodePtr value = readExpression();
        requireKeyword(Keyword::ParenEnd);
        line.reset(new ast::Print{std::move(value)});
    } else if (checkKeyword(Keyword::Map)) {
        line = readMap();
    } else if (checkKeyword(Keyword::Filter)) {
        line = readFilter();
    } else if (checkKeyword(Keyword::If)) {
        return readCond();
    } else if (checkKeyword(Keyword::For)) {
        return readLoop();
    } else if (!is_toplevel && checkKeyword(Keyword::BlockEnd)) {
        return nullptr;
    } else if (is_toplevel && lexer->eof()){
        return nullptr;
    } else {
        throw unexpected_input(getToken());
    }

    requireKeyword(Keyword::Semicolon);
    return line;
}

Parser::NodePtr Parser::readLines(bool is_toplevel)
{
    std::vector<NodePtr> subtrees;
    NodePtr line;
    while ((line = readBlockOrLine(is_toplevel)) != nullptr) {
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
    std::unique_ptr<ast::Assign> assignment{new ast::Assign{varname->asVar(), std::move(value)}};
    NodePtr declaration{new ast::Declaration{std::move(assignment)}};
    return declaration;
}

Parser::NodePtr Parser::readCall(const std::string& varname)
{
    if (checkKeyword(Keyword::ParenEnd)) {
        NodePtr call{new ast::Call{varname}};
        return call;
    } else {
        NodePtr tuple = readTuple();
        requireKeyword(Keyword::ParenEnd);
        NodePtr call{new ast::Call{varname, std::move(tuple)}};
        return call;
    }
}

Parser::NodePtr Parser::readCond()
{
    requireKeyword(Keyword::ParenBegin);
    NodePtr condition = readExpression();
    requireKeyword(Keyword::ParenEnd);
    NodePtr block = readBlockOrLine();

    if (checkKeyword(Keyword::Else)) {
        NodePtr else_block = readBlockOrLine();
        NodePtr cond{new ast::Cond{std::move(condition), std::move(block), std::move(else_block)}};
        return cond;
    } else {
        NodePtr cond{new ast::Cond{std::move(condition), std::move(block)}};
        return cond;
    }
}

Parser::NodePtr Parser::readLoop()
{
    requireKeyword(Keyword::ParenBegin);
    TokenPtr varname = requireToken(Token::Type::Var);
    requireKeyword(Keyword::In);
    NodePtr collection = readExpression();
    requireKeyword(Keyword::ParenEnd);
    NodePtr block = readBlockOrLine();

    NodePtr loop{new ast::Loop{varname->asVar(), std::move(collection), std::move(block)}};
    return loop;
}

Parser::NodePtr Parser::readMap()
{
    requireKeyword(Keyword::ParenBegin);
    NodePtr fun = readExpression();
    requireKeyword(Keyword::Comma);
    NodePtr list = readExpression();
    requireKeyword(Keyword::ParenEnd);

    NodePtr map{new ast::Map{std::move(fun), std::move(list)}};
    return map;
}

Parser::NodePtr Parser::readFilter()
{
    requireKeyword(Keyword::ParenBegin);
    NodePtr fun = readExpression();
    requireKeyword(Keyword::Comma);
    NodePtr list = readExpression();
    requireKeyword(Keyword::ParenEnd);

    NodePtr filter{new ast::Filter{std::move(fun), std::move(list)}};
    return filter;
}

Parser::NodePtr Parser::readExpression()
{
    return readComparison();
}

Parser::NodePtr Parser::readOperator(
    NodePtr (Parser::*readNextExpression)(),
    const std::initializer_list<Keyword>& operators)
{
    NodePtr lhs = (this->*readNextExpression)();
    while (TokenPtr token{checkKeywords(operators)}) {
        Keyword op = token->asKeyword();
        NodePtr rhs = (this->*readNextExpression)();
        lhs.reset(new ast::BinaryOperator{op, std::move(lhs), std::move(rhs)});
    }

    return lhs;
}

Parser::NodePtr Parser::readComparison()
{
    return readOperator(
        &Parser::readSum,
        {Keyword::Equals, Keyword::NotEquals});
}

Parser::NodePtr Parser::readSum()
{
    return readOperator(
        &Parser::readMult,
        {Keyword::Plus, Keyword::Minus});
}

Parser::NodePtr Parser::readMult()
{
    return readOperator(
        &Parser::readValue,
        {Keyword::Mult, Keyword::Div});
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
    } else if (checkKeyword(Keyword::Map)) {
        return readMap();
    } else if (checkKeyword(Keyword::Filter)) {
        return readFilter();
    } else if (checkKeyword(Keyword::ParenBegin)) {
        NodePtr expr = readExpression();
        requireKeyword(Keyword::ParenEnd);
        return expr;
    } else if (checkKeyword(Keyword::Minus)) {
        NodePtr expr = readExpression();
        NodePtr unary{new ast::UnaryOperator{Keyword::Minus, std::move(expr)}};
        return unary;
    } else {
        return readLiteral();
    }
}

Parser::NodePtr Parser::readLiteral()
{
    if (TokenPtr num = checkToken(Token::Type::Number)) {
        NodePtr literal{new ast::NumberValue{static_cast<signed int>(num->asInt())}};
        return literal;
    } else if (checkKeyword(Keyword::ListBegin)) {
        if (checkKeyword(Keyword::ListEnd)) {
            NodePtr empty_list{new ast::Tuple};
            return empty_list;
        } else {
            NodePtr list = readTuple();
            requireKeyword(Keyword::ListEnd);
            return list;
        }
    } else {
        return readFunction();
    }
}

Parser::NodePtr Parser::readFunction()
{
    requireKeyword(Keyword::Fun);
    requireKeyword(Keyword::ParenBegin);
    if (checkKeyword(Keyword::ParenEnd)) {
        requireKeyword(Keyword::BlockBegin);
        NodePtr body = readLines();
        NodePtr function{new ast::FunctionValue{std::move(body)}};
        return function;
    } else {
        std::vector<std::string> args = readVarTuple();
        requireKeyword(Keyword::ParenEnd);
        requireKeyword(Keyword::BlockBegin);
        NodePtr body = readLines();
        NodePtr function{new ast::FunctionValue{std::move(args), std::move(body)}};
        return function;
    }
}

Parser::NodePtr Parser::readTuple()
{
    std::vector<NodePtr> expressions;

    // Empty tuple is handled by the caller.
    do {
        NodePtr expr = readExpression();
        expressions.push_back(std::move(expr));
    } while (checkKeyword(Keyword::Comma));

    NodePtr tuple{new ast::Tuple{std::move(expressions)}};
    return tuple;
}

std::vector<std::string> Parser::readVarTuple()
{
    std::vector<std::string> variables;

    // Empty tuple is handled by the caller.
    do {
        TokenPtr varname = requireToken(Token::Type::Var);
        variables.push_back(varname->asVar());
    } while (checkKeyword(Keyword::Comma));

    return variables;
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

Parser::TokenPtr Parser::checkKeywords(
    const std::initializer_list<Keyword>& expected)
{
    for (auto& keyword : expected) {
        if (TokenPtr token = checkKeyword(keyword)) {
            return token;
        }
    }

    return nullptr;
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
