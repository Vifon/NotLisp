// File: parser_tests.cpp

#include "catch.hpp"

#include <memory>
#include <sstream>

#include "../src/lexer/lexer.hpp"
#include "../src/parser/parser.hpp"

TEST_CASE("Parse a sample line", "[parser][assign]")
{
    std::stringstream stream{"var = value;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    ast->evaluate();
}

TEST_CASE("Parse multiple top-level lines", "[parser][assign]")
{
    std::stringstream stream{"var = value; var2 = 42;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    ast->evaluate();
}


TEST_CASE("Parse a declaration", "[parser][decl]")
{
    std::stringstream stream{"let var = value;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    ast->evaluate();
}

TEST_CASE("Parse a function call", "[parser][call][tuple]")
{
    std::stringstream stream{"myfun(arg); myfun2(arg1, arg2);"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(vfn::Lexer{stream})};

    auto ast = parser.parse();
    ast->evaluate();
}
