
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CARROT_DB_INCLUDE_DIR})

add_library(model STATIC value.cc)

# Tests
add_executable(model_test value_test.cc)
target_link_libraries(model_test gtest gtest_main model)

add_test(model_test model_test)