// File: tokens.hpp
#ifndef _h_VFN_TOKENS_
#define _h_VFN_TOKENS_

namespace vfn {

class Token
{
  public:
    virtual ~Token() = 0;
};

class NumberToken : public Token
{
  public:
    NumberToken(int);
    virtual ~NumberToken();
};


} // namespace vfn

#endif
