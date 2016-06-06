// File: eval_tests.cpp

#include "catch.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>

#include "../src/lexer/lexer.hpp"
#include "../src/parser/parser.hpp"

TEST_CASE("Read the variable value", "[eval][var][decl]")
{
    std::stringstream stream{"let v = 10; return v;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    auto ast = parser.parse();
    REQUIRE(ast->evaluate()->asInt() == 10);
}

TEST_CASE("Modify a variable value", "[eval][var][assign]")
{
    std::stringstream stream{"let v = 10; v = 20; return v;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    auto ast = parser.parse();
    auto result = ast->evaluate()->asInt();
    REQUIRE(result != 10);
    REQUIRE(result == 20);
}

TEST_CASE("Modify an outer variable in a nested scope", "[eval][var][assign][scope]")
{
    std::stringstream stream{"let v = 10; { v = 20; } return v;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();
    auto result = ast->evaluate()->asInt();
    REQUIRE(result != 10);
    REQUIRE(result == 20);
}

TEST_CASE("Modify an inner variable in a nested scope", "[eval][var][assign][scope]")
{
    std::stringstream stream{"let v = 10; { let v = 20; } return v;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();
    auto result = ast->evaluate()->asInt();
    REQUIRE(result != 20);
    REQUIRE(result == 10);
}

TEST_CASE("Call a function with wrong number of arguments", "[eval][function][args]")
{
    std::stringstream stream{R"(
let f = fun() {
  return 7;
};
f(5);
)"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();
    REQUIRE_THROWS_AS(ast->evaluate(), std::runtime_error);
}

TEST_CASE("Call a function", "[eval][function]")
{
    std::stringstream stream{R"(
let pow = fun(x) {
  return x*x;
};
pow(5);
)"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();
    REQUIRE(ast->evaluate()->asInt() == 25);
}
