include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CARROT_DB_INCLUDE_DIR})

# Tests
add_executable(rest_test rest_tests.cc)
target_link_libraries(rest_test gtest gtest_main carrot_db)

add_test(rest_test rest_test)