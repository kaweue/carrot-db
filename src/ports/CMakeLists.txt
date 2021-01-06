
include_directories(${CARROT_DB_INCLUDE_DIR})

add_library(ports STATIC key_services.cc)
target_link_libraries(ports adapters)