
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CARROT_DB_INCLUDE_DIR})

add_library(adapters STATIC api_service.cc get_request.cc post_request.cc path_to_key_id_service.cc)
target_link_libraries(adapters cpprest)

# Tests
add_executable(adapters_test api_service_test.cc post_request_test.cc get_request_test.cc)
target_link_libraries(adapters_test gtest gtest_main adapters)

add_test(adapters_test adapters_test)