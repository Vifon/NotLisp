// File: test.cpp

#include <iostream>
#include <memory>
#include <sstream>

#include "parser.hpp"

int main()
{
    const char* PROGRAM = R"(
let outer = 100;

let f = fun(x) {
  let a = 10;
  outer = outer + a;
  print(outer);     # 110 / 120
  print(42);        # 42
  print(x);         # 1 / 3
  a = x + a;
  return a;
};
f(1);
print(f(3));        # 13

let f2 = fun(l) {
  let a = 10;
  for (i in l) {
    print(i + a);
  }
};
f2([1, 2, 3]);


print([1, 2, 3]);
print([1,[2,3,4,
5],   6]);
print(f);
print(fun(){});

let pred = fun(x) {
  if (x == 2) {
    return [];
  } else {
    return 1;
  }
};

let l = [1, 2, 3, 4];
print(l);
print(filter(pred, l));

let void = fun(){};
print(void());

let pow = fun(x) { return x*x; };
print(pow(25));

print(map(pow, l));
)";

    std::stringstream stream{PROGRAM};
    vfn::Parser p{std::make_unique<vfn::Lexer>(stream)};

    try {
        p.parse()->run();
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
