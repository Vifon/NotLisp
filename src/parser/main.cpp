// File: main.cpp

#include <iostream>
#include <memory>
#include <sstream>

#include "parser.hpp"

int main(int argc, char *argv[])
{
    const char* PROGRAM = R"(
let v = 10;
for (i in [1, 2, 3]) {
  let v2 = i + v;
  print(v);
  print(i);
  print(v2);
}
)";

    std::stringstream stream{PROGRAM};
    vfn::Parser p{std::make_unique<vfn::Lexer>(stream)};

    p.parse()->evaluate();

    return 0;
}
