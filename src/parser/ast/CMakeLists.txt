set(ast_SOURCES
  Value.cpp
  )

set(ast_HEADERS
  Assign.hpp
  BinaryOperator.hpp
  Block.hpp
  Call.hpp
  Cond.hpp
  Declaration.hpp
  Filter.hpp
  FunctionValue.hpp
  ListValue.hpp
  Loop.hpp
  Map.hpp
  Node.hpp
  NumberValue.hpp
  Print.hpp
  Return.hpp
  Tuple.hpp
  UnaryOperator.hpp
  Value.hpp
  Variable.hpp
  VoidValue.hpp
  bad_result_cast.hpp
  )

add_library(ast STATIC ${ast_SOURCES})
