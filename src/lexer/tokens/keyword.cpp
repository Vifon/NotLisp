// File: keyword.cpp

#include "keyword.hpp"

#include <map>

namespace vfn {

#define GEN_MAP(X) {(Keyword::X), ("'"#X"'")}
static const std::map<Keyword, std::string> keyword_rev_mapping{{
        GEN_MAP(ParenBegin),
        GEN_MAP(ParenEnd),
        GEN_MAP(ListBegin),
        GEN_MAP(ListEnd),
        GEN_MAP(BlockBegin),
        GEN_MAP(BlockEnd),
        GEN_MAP(If),
        GEN_MAP(Else),
        GEN_MAP(Let),
        GEN_MAP(Fun),
        GEN_MAP(For),
        GEN_MAP(In),
        GEN_MAP(Return),
        GEN_MAP(Print),
        GEN_MAP(Map),
        GEN_MAP(Filter),
        GEN_MAP(Plus),
        GEN_MAP(Minus),
        GEN_MAP(Mult),
        GEN_MAP(Div),
        GEN_MAP(Assignment),
        GEN_MAP(Equals),
        GEN_MAP(NotEquals),
        GEN_MAP(Comma),
        GEN_MAP(Semicolon),
    }};
#undef GEN_MAP

/**
 * Stringify a keyword.
 */
std::ostream& operator<<(std::ostream& out, Keyword keyword)
{
    return out << keyword_rev_mapping.at(keyword);
}

} // namespace vfn
