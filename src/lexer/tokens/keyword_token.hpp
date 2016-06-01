// File: keyword_token.hpp
#ifndef _h_VFN_KEYWORD_TOKEN_
#define _h_VFN_KEYWORD_TOKEN_

#include <ostream>
#include <string>

#include "keyword.hpp"
#include "token.hpp"

namespace vfn {

/**
 * A keyword token with discrete values.
 */
class KeywordToken : public Token
{
  public:
    KeywordToken(Keyword s);
    KeywordToken(const std::string& s);

    Keyword asKeyword() const override
    {
        return keyword;
    }

    bool operator==(Keyword keyword) const override
    {
        return asKeyword() == keyword;
    }

    Token* clone() const override
    {
        return new KeywordToken(*this);
    }

    std::ostream& show(std::ostream& out) const override;

    /**
     * The represented keyword.
     */
    const Keyword keyword;
};

} // namespace vfn

#endif
