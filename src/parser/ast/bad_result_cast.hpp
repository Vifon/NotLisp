// File: bad_result_cast.hpp
#pragma once

#include <exception>

namespace vfn {

namespace ast {

class bad_result_cast : public std::exception
{
  public:
    bad_result_cast(const char* msg)
        : message(msg)
    { }

    bad_result_cast()
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
