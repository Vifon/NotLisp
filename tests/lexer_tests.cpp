// File: lexer_tests.cpp

#include "catch.hpp"

#include <sstream>

#include "../src/lexer/lexer.hpp"

const char* EXAMPLE_CODE =
    "list = [5, 6, 7];";

TEST_CASE("Lexer dummy", "[lexer]")
{
    std::stringstream stream{EXAMPLE_CODE};
    vfn::Lexer l{stream};

    REQUIRE(dynamic_cast<vfn::InvalidToken*>(&l.readToken()) != nullptr);
}
