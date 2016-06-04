set(tokens_SOURCES
  bad_token_cast.cpp
  keyword.cpp
  keyword_token.cpp
  token.cpp
  )

set(tokens_HEADERS
  bad_token_cast.hpp
  eof_token.hpp
  invalid_token.hpp
  keyword.hpp
  keyword_token.hpp
  number_token.hpp
  token.hpp
  var_token.hpp
  )

add_library(tokens STATIC ${tokens_SOURCES})
