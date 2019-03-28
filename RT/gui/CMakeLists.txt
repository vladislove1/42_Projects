cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

set( GUI_FILES  gui.cpp
                gui.h
                gl_program_init.c )
PREPEND( GUI ${CMAKE_CURRENT_SOURCE_DIR}/ ${GUI_FILES} )

target_sources( RT PRIVATE ${GUI} )
target_include_directories( RT PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
