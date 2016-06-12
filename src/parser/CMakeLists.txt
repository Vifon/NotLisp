set(parser_SOURCES
  parser.cpp
  )

set(parser_HEADERS
  parser.hpp
  UnexpectedInput.hpp
  )

add_library(parser STATIC ${parser_SOURCES})
target_link_libraries(parser
  lexer
  ast)

add_executable(parser_test main.cpp)
target_link_libraries(parser_test
  parser)

add_subdirectory(ast)
