// File: main.cpp

#include <iostream>
#include <memory>
#include <sstream>

#include "parser.hpp"

int main(int argc, char *argv[])
{
    /*
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
    /*/
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
    //*/

    std::stringstream stream{PROGRAM};
    vfn::Parser p{std::make_unique<vfn::Lexer>(stream)};

    try {
        p.parse()->evaluate();
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
