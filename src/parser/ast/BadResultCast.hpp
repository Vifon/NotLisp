// File: BadResultCast.hpp
#pragma once

#include <exception>

namespace vfn {

namespace ast {

class BadResultCast : public std::exception
{
  public:
    BadResultCast(const char* msg)
        : message(msg)
    { }

    BadResultCast()
        : message("")
    { }

    const char* what() const noexcept override
    {
        return message;
    }

  private:
    const char* message;
};

} // namespace ast

} // namespace vfn
