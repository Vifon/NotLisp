set(tokens_SOURCES
  keyword.cpp
  keyword_token.cpp
  token.cpp
  )

set(tokens_HEADERS
  bad_token_cast.hpp
  invalid_token.hpp
  keyword.hpp
  keyword_token.hpp
  number_token.hpp
  token.hpp
  var_token.hpp
  )

add_library(tokens STATIC ${tokens_SOURCES})
