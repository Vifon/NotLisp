set(lexer_SOURCES
  lexer.cpp
  tokens.cpp
  )

set(lexer_HEADERS
  lexer.hpp
  tokens.hpp
  )

add_library(lexer STATIC ${lexer_SOURCES})
