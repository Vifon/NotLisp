// File: UnexpectedInput.hpp
#pragma once

#include <exception>
#include <sstream>

namespace vfn {

class UnexpectedInput : public std::exception
{
  public:
    UnexpectedInput(unsigned int line, const Token& token)
        : message("Unexpected token at line ")
    {
        std::stringstream ss;
        ss << line << ": ";
        ss << token;
        message += ss.str();
    }

    UnexpectedInput()
        : message("Unexpected token")
    { }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

  private:
    std::string message;
};

} // namespace vfn
