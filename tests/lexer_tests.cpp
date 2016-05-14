// File: lexer_tests.cpp

#include "catch.hpp"

#include <sstream>

#include "../src/lexer/lexer.hpp"
#include "../src/lexer/tokens.hpp"

TEST_CASE("Scan no valid tokens", "[lexer]")
{
    std::stringstream stream;

    SECTION("Empty input") {
        stream.str("");
    }

    SECTION("Invalid input") {
        stream.str(".....");
    }

    SECTION("Only comments") {
        stream.str("# this is a comment");
    }

    vfn::Lexer l{stream};

    REQUIRE_FALSE(l.readToken().isValid());
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

    REQUIRE_FALSE(l.readToken().isValid());
    REQUIRE(l.tokensRead() == 1);
}

TEST_CASE("Scan multiple integers", "[lexer][int]")
{
    std::stringstream stream{"42 130 1000"};
    vfn::Lexer l{stream};

    REQUIRE(l.readToken().asInt() == 42);
    REQUIRE(l.readToken().asInt() == 130);
    REQUIRE(l.readToken().asInt() == 1000);
    REQUIRE_FALSE(l.readToken().isValid());

    REQUIRE(l.tokensRead() == 3);
}

TEST_CASE("Scan integers with comments", "[lexer][int][comment]")
{
    std::stringstream stream{(
            "42   # A nice number indeed\n"
            "107  # Another one\n"
            "# Let's throw in some commented numbers: 12 83\n"
            "     # A comment with only whitespace before it\n"
            "0    # Let's end it with a zero\n"
            )};
    vfn::Lexer l{stream};

    REQUIRE(l.readToken().asInt() == 42);
    REQUIRE(l.readToken().asInt() == 107);
    REQUIRE(l.readToken().asInt() == 0);
    REQUIRE_FALSE(l.readToken().isValid());

    REQUIRE(l.tokensRead() == 3);
}

TEST_CASE("Differentiate the assignment and equality operators", "[lexer][keyword][operator]")
{
    std::stringstream stream{"= == = === ====  ===== ="};
    vfn::Lexer l{stream};

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Equals);

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Equals);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Equals);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Equals);

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Equals);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Equals);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);

    REQUIRE_FALSE(l.readToken().isValid());

    REQUIRE(l.tokensRead() == 11);
}

TEST_CASE("Scan an assignment expression", "[lexer][keyword][var][int]")
{
    std::stringstream stream{"let myvar = 17;"};
    vfn::Lexer l{stream};

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Let);
    REQUIRE(l.readToken().asVar() == "myvar");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);
    REQUIRE(l.readToken().asInt() == 17);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE_FALSE(l.readToken().isValid());

    REQUIRE(l.tokensRead() == 5);
}

TEST_CASE("Scan a variable starting with a keyword-like prefix", "[lexer][keyword][var]")
{
    std::stringstream stream{"letshavesomefun with prefixes;"};
    vfn::Lexer l{stream};

    REQUIRE(l.readToken().asVar() == "letshavesomefun");
    REQUIRE(l.readToken().asVar() == "with");
    REQUIRE(l.readToken().asVar() == "prefixes");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE_FALSE(l.readToken().isValid());

    REQUIRE(l.tokensRead() == 4);
}

TEST_CASE("Scan an example program", "[lexer][int][list][block][keyword][var]")
{
    const char* PROGRAM = R"(
map(fun(x) { return x+42; },
    [1, 2, 3, 4]));  # => [43, 44, 45, 46]

list = [5, 6, 7];
multiply_by_2 = fun(x) {
    return x*2;
};
map(multiply_by_2, list);  # => [10, 12, 14]

nested_list = [[1, 2], [3, 4], [5, 6]];
map(car, nested_list);  # => [1, 3, 5]
map(cdr, nested_list);  # => [[2], [4], [6]]
map(car, map(cdr, nested_list));  # => [2, 4, 6]
)";

    std::stringstream stream{PROGRAM};
    vfn::Lexer l{stream};

    REQUIRE(l.readToken().asVar() == "map");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenBegin);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Fun);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenBegin);
    REQUIRE(l.readToken().asVar() == "x");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::BlockBegin);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Return);
    REQUIRE(l.readToken().asVar() == "x");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Plus);
    REQUIRE(l.readToken().asInt() == 42);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::BlockEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);

    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListBegin);
    REQUIRE(l.readToken().asInt() == 1);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asInt() == 2);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asInt() == 3);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asInt() == 4);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE(l.readToken().asVar() == "list");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListBegin);
    REQUIRE(l.readToken().asInt() == 5);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asInt() == 6);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asInt() == 7);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE(l.readToken().asVar() == "multiply_by_2");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Fun);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenBegin);
    REQUIRE(l.readToken().asVar() == "x");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::BlockBegin);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Return);
    REQUIRE(l.readToken().asVar() == "x");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Mult);
    REQUIRE(l.readToken().asInt() == 2);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::BlockEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE(l.readToken().asVar() == "map");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenBegin);
    REQUIRE(l.readToken().asVar() == "multiply_by_2");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asVar() == "list");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE(l.readToken().asVar() == "nested_list");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Assignment);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListBegin);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListBegin);
    REQUIRE(l.readToken().asInt() == 1);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asInt() == 2);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListBegin);
    REQUIRE(l.readToken().asInt() == 3);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asInt() == 4);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListBegin);
    REQUIRE(l.readToken().asInt() == 5);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asInt() == 6);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ListEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE(l.readToken().asVar() == "map");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenBegin);
    REQUIRE(l.readToken().asVar() == "car");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asVar() == "nested_list");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE(l.readToken().asVar() == "map");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenBegin);
    REQUIRE(l.readToken().asVar() == "cdr");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asVar() == "nested_list");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE(l.readToken().asVar() == "map");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenBegin);
    REQUIRE(l.readToken().asVar() == "car");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asVar() == "map");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenBegin);
    REQUIRE(l.readToken().asVar() == "cdr");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Comma);
    REQUIRE(l.readToken().asVar() == "nested_list");
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::ParenEnd);
    REQUIRE(l.readToken().asKeyword() == vfn::Keyword::Semicolon);

    REQUIRE_FALSE(l.readToken().isValid());
}
