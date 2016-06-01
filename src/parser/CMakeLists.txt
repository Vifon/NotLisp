set(parser_SOURCES
  parser.cpp
  )

set(parser_HEADERS
  parser.hpp
  )

add_library(parser STATIC ${parser_SOURCES})
target_link_libraries(parser
  lexer)

add_executable(parser_test main.cpp)
target_link_libraries(parser_test
  parser)
