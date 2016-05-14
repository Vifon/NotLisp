// File: token.cpp

#include "token.hpp"

namespace vfn {

/**
 * Stringify a token.
 */
std::ostream& operator<<(std::ostream& out, const Token& token)
{
    return token.show(out);
}

} // namespace vfn
