// File: notlisp.cpp

#include <iostream>
#include <memory>
#include <sstream>

#include "parser.hpp"

int main()
{
    vfn::Parser p{std::make_unique<vfn::Lexer>(std::cin)};

    try {
        p.parse()->run();
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
