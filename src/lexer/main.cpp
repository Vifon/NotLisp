// File: main.cpp

#include <iostream>
#include <sstream>

#include "lexer.hpp"

int main()
{
    const char* PROGRAM = R"(
map(fun(x) { return x+42; },
    [1, 2, 3, 4]));  # => [43, 44, 45, 46]

list = [5, 6, 7];
multiply_by_2 = fun(x) {
    return x*2;
};
map(multiply_by_2, list);  # => [10, 12, 14]

nested_list = [[1, 2], [3, 4], [5, 6]];
map(car, nested_list);  # => [1, 3, 5]
map(cdr, nested_list);  # => [[2], [4], [6]]
map(car, map(cdr, nested_list));  # => [2, 4, 6]
)";

    std::stringstream stream{PROGRAM};
    vfn::Lexer l{stream};

    while (l.readToken().isValid()) {
        std::cout << l.getToken() << "   ";
    }
    std::cout << std::endl;

    return 0;
}
