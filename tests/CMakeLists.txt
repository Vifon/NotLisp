set(tests_SOURCES
  catch_main.cpp
  constants.cpp
  lexer_tests.cpp
  parser_tests.cpp
  )

set(tests_HEADERS
  catch.hpp
  constants.hpp
  )

add_executable(test_all ${tests_SOURCES})
target_link_libraries(test_all
  lexer
  parser)
