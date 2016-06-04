// File: parser_tests.cpp

#include "catch.hpp"

#include <memory>
#include <sstream>

#include "../src/lexer/lexer.hpp"
#include "../src/parser/parser.hpp"
#include "constants.hpp"

TEST_CASE("Parse a sample line", "[parser][assign]")
{
    std::stringstream stream{"var = value;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    // ast->evaluate();
}

TEST_CASE("Parse multiple top-level lines", "[parser][assign]")
{
    std::stringstream stream{"var = value; var2 = 42;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    // ast->evaluate();
}


TEST_CASE("Parse a declaration", "[parser][decl]")
{
    std::stringstream stream{"let var = value;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    // ast->evaluate();
}

TEST_CASE("Parse a function call", "[parser][call][tuple]")
{
    std::stringstream stream{"myfun(arg); myfun2(arg1, arg2);"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    // ast->evaluate();
}

TEST_CASE("Detect an invalid token", "[parser][error]")
{
    std::stringstream stream{"myfun(arg)|;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    vfn::Parser::NodePtr ast;
    REQUIRE_THROWS_AS(ast = parser.parse(), vfn::unexpected_input);
    REQUIRE(ast == nullptr);
}

TEST_CASE("Detect an unexpected EOF", "[parser][error]")
{
    std::stringstream stream{"myfun(arg)"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    vfn::Parser::NodePtr ast;
    REQUIRE_THROWS_AS(ast = parser.parse(), vfn::unexpected_input);
    REQUIRE(ast == nullptr);
}

TEST_CASE("Parse a return statement", "[parser][return]")
{
    std::stringstream stream{"return 42;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
}

TEST_CASE("Parse a complex expression", "[parser][expr]")
{
    std::stringstream stream{"return 7-10*2+8*1*(2+1);"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    REQUIRE(ast->evaluate()->asInt() == 11);
}

TEST_CASE("Parse an example program", "[parser][example]")
{
    std::stringstream stream{PROGRAM};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    REQUIRE_NOTHROW(parser.parse());
}
