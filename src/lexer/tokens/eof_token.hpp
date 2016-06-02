// File: eof_token.hpp
#pragma once

#include "invalid_token.hpp"

namespace vfn {

/**
 * A pseudo-token indicating the end of file.
 */
class EOFToken : public InvalidToken
{
  public:
    std::ostream& show(std::ostream& out) const override
    {
        return out << "[EOF]";
    }
};

} // namespace vfn
