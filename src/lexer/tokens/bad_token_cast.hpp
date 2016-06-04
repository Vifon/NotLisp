// File: bad_token_cast.hpp
#ifndef _h_VFN_BAD_TOKEN_CAST_
#define _h_VFN_BAD_TOKEN_CAST_

#include <exception>
#include <sstream>
#include <string>

namespace vfn {

class Token;

/**
 * Invalid @p Token type for the used operation.
 */
class bad_token_cast : public std::exception
{
  public:
    bad_token_cast(const char* msg, const Token& token);
    bad_token_cast(const char* msg);
    bad_token_cast();

    const char* what() const noexcept override;

  private:
    std::string message;
};

} // namespace vfn

#endif
