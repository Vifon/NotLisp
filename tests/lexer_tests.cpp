// File: lexer_tests.cpp

#include "catch.hpp"

#include <sstream>

#include "../src/lexer/lexer.hpp"

TEST_CASE("Scan no valid tokens", "[lexer]")
{
    std::stringstream stream;

    SECTION("Empty input") {
        stream.str("");
    }

    SECTION("Invalid input") {
        stream.str(",,,,");
    }

    vfn::Lexer l{stream};

    REQUIRE(!l.readToken().isValid());
    REQUIRE(l.tokensRead() == 0);
}

TEST_CASE("Scan integer", "[lexer][int]")
{
    std::stringstream stream{"42"};
    vfn::Lexer l{stream};

    auto& token = l.readToken();
    REQUIRE(token.isValid());
    REQUIRE(typeid(token) == typeid(vfn::NumberToken));

    auto num_token = dynamic_cast<vfn::NumberToken*>(&token);
    REQUIRE(num_token != nullptr);
    REQUIRE(l.getToken().asInt() == 42);

    REQUIRE(l.tokensRead() == 1);
}

TEST_CASE("Scan integer zero", "[lexer][int]")
{
    std::stringstream stream{"0 00"};
    vfn::Lexer l{stream};

    REQUIRE(l.readToken().isValid());
    REQUIRE(l.getToken().asInt() == 0);

    REQUIRE(!l.readToken().isValid());
    REQUIRE(l.tokensRead() == 1);
}

TEST_CASE("Scan multiple integers", "[lexer][int]")
{
    std::stringstream stream{"42 130 1000"};
    vfn::Lexer l{stream};

    REQUIRE(l.readToken().asInt() == 42);
    REQUIRE(l.readToken().asInt() == 130);
    REQUIRE(l.readToken().asInt() == 1000);
    REQUIRE(!l.readToken().isValid());

    REQUIRE(l.tokensRead() == 3);
}
