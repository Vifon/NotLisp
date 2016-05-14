// File: tokens.cpp

#include "tokens.hpp"

namespace vfn {

const std::map<std::string, Keyword> KeywordToken::mapping{{
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

} // namespace vfn
