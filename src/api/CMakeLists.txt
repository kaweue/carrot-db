
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CARROT_DB_INCLUDE_DIR})

add_library(api_service api_service.cc)
target_link_libraries(api_service cpprest)

# Tests
add_executable(api_test api_service_test.cc)
target_link_libraries(api_test gtest gtest_main api_service)

add_test(api_test api_test)