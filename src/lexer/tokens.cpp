// File: tokens.cpp

#include "tokens.hpp"

#include <map>

namespace vfn {

#define GEN_MAP(X) {(Keyword::X), (#X)}
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

static const std::map<std::string, Keyword> keyword_mapping{{
        {"("      , Keyword::ParenBegin},
        {")"      , Keyword::ParenEnd},
        {"["      , Keyword::ListBegin},
        {"]"      , Keyword::ListEnd},
        {"{"      , Keyword::BlockBegin},
        {"}"      , Keyword::BlockEnd},
        {"if"     , Keyword::If},
        {"else"   , Keyword::Else},
        {"let"    , Keyword::Let},
        {"fun"    , Keyword::Fun},
        {"for"    , Keyword::For},
        {"in"     , Keyword::In},
        {"return" , Keyword::Return},
        {"+"      , Keyword::Plus},
        {"-"      , Keyword::Minus},
        {"*"      , Keyword::Mult},
        {"/"      , Keyword::Div},
        {"="      , Keyword::Assignment},
        {"=="     , Keyword::Equals},
        {"!="     , Keyword::NotEquals},
        {","      , Keyword::Comma},
        {";"      , Keyword::Semicolon},
    }};

KeywordToken::KeywordToken(const std::string& s)
    : keyword(keyword_mapping.at(s))
{ }

std::ostream& KeywordToken::show(std::ostream& out) const
{
    return out << "[keyword: " << asKeyword() << "]";
}

/**
 * Stringify a token.
 */
std::ostream& operator<<(std::ostream& out, const Token& token)
{
    return token.show(out);
}

/**
 * Stringify a keyword.
 */
std::ostream& operator<<(std::ostream& out, Keyword keyword)
{
    return out << keyword_rev_mapping.at(keyword);
}

} // namespace vfn
