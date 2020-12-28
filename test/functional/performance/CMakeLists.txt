include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CARROT_DB_INCLUDE_DIR})

# Tests
add_executable(performance_tests performance_tests.cc)
target_link_libraries(performance_tests gtest gtest_main carrot_db)

add_test(performance_test performance_tests)