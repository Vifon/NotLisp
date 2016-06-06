// File: main.cpp

#include <iostream>
#include <memory>
#include <sstream>

#include "parser.hpp"

int main(int argc, char *argv[])
{
    const char* PROGRAM = R"(
let v = 10;
let v2 = 6;
for (i in [1, 2, 3]) {
  let v3 = i + v;
  v2 = v2 + 2;
  print(i);
  print(v);
  print(v2);
  print(v3);
  if (v == v2) {
    print(42);
  }
}

for (i in [1, 2, 3]) {
  print(v);
  let v = i + v;
  print(i);
  print(v);
}

for (i in [1, 4, 8]) print(i);
)";

    std::stringstream stream{PROGRAM};
    vfn::Parser p{std::make_unique<vfn::Lexer>(stream)};

    try {
        p.parse()->evaluate();
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
