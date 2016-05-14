// File: bad_token_cast.hpp
#ifndef _h_VFN_BAD_TOKEN_CAST_
#define _h_VFN_BAD_TOKEN_CAST_

#include <exception>

namespace vfn {

/**
 * Invalid @p Token type for the used operation.
 */
class bad_token_cast : public std::exception
{
  public:
    bad_token_cast(const char* msg)
        : message(msg)
    { }

    bad_token_cast()
        : message("")
    { }

    const char* what() const noexcept override
    {
        return message;
    }

  private:
    const char* message;
};

} // namespace vfn

#endif
