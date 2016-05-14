// File: tokens.cpp

#include "tokens.hpp"

namespace vfn {

/**
 * Try to read the numerical value of this token.
 */
int Token::asInt()
{
    return dynamic_cast<NumberToken&>(*this).getValue();
}

} // namespace vfn
