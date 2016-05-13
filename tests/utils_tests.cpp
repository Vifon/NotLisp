// File: utils_tests.cpp

#include "catch.hpp"

#include "../src/utils.hpp"

using namespace vfn;

Maybe<int> halve(int n)
{
    if (n & 1) {
        return Nothing;
    } else {
        return Just(n/2);
    }
}

Maybe<int> halve_ref(int& n)
{
    if (n & 1) {
        return Nothing;
    } else {
        return Just(n/2);
    }
}

TEST_CASE("Maybe monad", "[util][maybe]")
{
    Maybe<int> n = Just(100);

    SECTION("Successful computation") {
        auto result = n >> halve >> halve;
        REQUIRE(result);
        REQUIRE(*result == 25);
    }

    SECTION("Empty result") {
        auto result = n >> halve >> halve >> halve >> halve;
        REQUIRE(!result);
        REQUIRE(result == Nothing);
    }

    SECTION("Function with referential argument") {
        auto result = n >> halve_ref;
        REQUIRE(result);
    }

    SECTION("Lambda application") {
        auto halve_lambda = [](int n) -> Maybe<int> {
            if (n & 1) {
                return Nothing;
            } else {
                return Just(n/2);
            }
        };

        auto result = n >> halve_lambda >> halve_lambda;
        REQUIRE(result);
        REQUIRE(*result == 25);
    }
}
