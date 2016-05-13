set(tests_SOURCES
  catch_main.cpp
  utils_tests.cpp
  )

set(tests_HEADERS
  catch.hpp
  )

add_executable(test_all ${tests_SOURCES})
