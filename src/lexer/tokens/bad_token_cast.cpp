// File: bad_token_cast.cpp

#include "bad_token_cast.hpp"

#include "token.hpp"

namespace vfn {

bad_token_cast::bad_token_cast(const char* msg, const Token& token)
    : message(msg)
{
    std::stringstream ss;
    ss << token;
    message += ss.str();
}

bad_token_cast::bad_token_cast(const char* msg)
    : message(msg)
{ }

bad_token_cast::bad_token_cast()
    : message("")
{ }

const char* bad_token_cast::what() const noexcept
{
    return message.c_str();
}

} // namespace vfn
