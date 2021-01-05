
include_directories(${CARROT_DB_INCLUDE_DIR})

add_library(carrot_db STATIC carrot_db.cc)
target_link_libraries(carrot_db cpprest adapters ports)
