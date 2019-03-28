cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

include_directories( ${OpenCL_INCLUDE_DIR} )

set (SOURCE_FILES	cl.h
					cl_buffer.c
					cl_init.c
					cl_kernel.c
					cl_private.h )

PREPEND(SOURCES ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCE_FILES})

target_sources( RT PUBLIC ${SOURCES} )
target_include_directories( RT PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

