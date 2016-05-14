set(lexer_SOURCES
  lexer.cpp
  )

set(lexer_HEADERS
  lexer.hpp
  )

add_library(lexer STATIC ${lexer_SOURCES})
target_link_libraries(lexer
  tokens)

add_executable(lexer_test main.cpp)
target_link_libraries(lexer_test
  lexer)

add_subdirectory(tokens)

