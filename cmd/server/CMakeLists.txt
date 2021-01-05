include_directories(${CARROT_DB_INCLUDE_DIR})

add_executable(server main.cc)

target_link_libraries(server carrot_db)

install(TARGETS server RUNTIME DESTINATION bin)