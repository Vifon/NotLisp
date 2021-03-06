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
    REQUIRE(ast->run()->asInt() == 10);
}

TEST_CASE("Modify a variable value", "[eval][var][assign]")
{
    std::stringstream stream{"let v = 10; v = 20; return v;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    auto ast = parser.parse();
    auto result = ast->run()->asInt();
    REQUIRE(result != 10);
    REQUIRE(result == 20);
}

TEST_CASE("Modify an outer variable in a nested scope", "[eval][var][assign][scope]")
{
    std::stringstream stream{"let v = 10; { v = 20; } return v;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();
    auto result = ast->run()->asInt();
    REQUIRE(result != 10);
    REQUIRE(result == 20);
}

TEST_CASE("Modify an inner variable in a nested scope", "[eval][var][assign][scope]")
{
    std::stringstream stream{"let v = 10; { let v = 20; } return v;"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();
    auto result = ast->run()->asInt();
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
    REQUIRE_THROWS_AS(ast->run(), std::runtime_error);
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
    REQUIRE(ast->run()->asInt() == 25);
}

TEST_CASE("Call a function with conflicting argument names", "[eval][function][args]")
{
    std::stringstream stream{R"(
let f = fun(x, x, z) {
  return 7;
};
f(1, 2, 3);
)"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();
    REQUIRE_THROWS_AS(ast->run(), std::runtime_error);
}

TEST_CASE("Pass a variable to a function", "[eval][function][args][var]")
{
    std::stringstream stream{R"(
let f = fun(a) {
  a = a + 1;
  return a;
};
let x = 5;
return f(x);
)"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();
    REQUIRE(ast->run()->asInt() == 6);
}

TEST_CASE("Filter a list", "[eval][filter][function][cond]")
{
    std::stringstream stream{R"(
let pred = fun(x) {
  if (x == 2)
    return [];
  else
    return 1;
};
return filter(pred, [1, 2, 3, 4]);
)"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();

    std::stringstream output;
    output << *ast->run();
    REQUIRE(output.str() == "[1, 3, 4]");
}

TEST_CASE("Map a function over a list", "[eval][map][function]")
{
    std::stringstream stream{R"(
let pow = fun(x) { return x*x; };
return map(pow, [1, 2, 3, 4, 5]);
)"};
    vfn::Parser parser{std::make_unique<vfn::Lexer>(stream)};

    vfn::Parser::NodePtr ast;
    ast = parser.parse();

    std::stringstream output;
    output << *ast->run();
    REQUIRE(output.str() == "[1, 4, 9, 16, 25]");
}
