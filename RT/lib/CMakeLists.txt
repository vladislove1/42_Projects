cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

add_subdirectory( libft )
add_subdirectory( imgui )
add_subdirectory( cJSON )

set( LIBRARY_INCLUDES ${LIBFT_INCLUDES} ${IMGUI_INCLUDES} PARENT_SCOPE )
set( LIBRARY_INCLUDE_DIR ${LIBRARY_INCLUDE_DIR} ${LIBFT_INCLUDE_DIR} ${IMGUI_INCLUDE_DIR} ${IMGUI_INCLUDE_DIR}/examples PARENT_SCOPE )
