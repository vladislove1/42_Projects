cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

set( LIBRARY_INCLUDE_DIR ${LIBRARY_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/cjson PARENT_SCOPE )

add_subdirectory( sources )
