// File: keyword_token.cpp

#include "keyword_token.hpp"

#include <map>

namespace vfn {

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

KeywordToken::KeywordToken(Keyword s)
    : Token(TokenType::Keyword)
    , keyword(s)
{ }

KeywordToken::KeywordToken(const std::string& s)
    : Token(TokenType::Keyword)
    , keyword(keyword_mapping.at(s))
{ }

std::ostream& KeywordToken::show(std::ostream& out) const
{
    return out << "[keyword: " << asKeyword() << "]";
}

} // namespace vfn
