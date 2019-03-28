cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

include_directories( . )

set( IMGUI_INCLUDE_DIR   ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

set (IMGUI_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/imgui.h PARENT_SCOPE) 


set( IMGUI_FILES	imconfig.h
					imgui.cpp
					imgui.h
					imgui_demo.cpp
					imgui_draw.cpp
					imgui_impl_sdl_gl3.cpp
					imgui_impl_sdl_gl3.h
					imgui_internal.h
					stb_rect_pack.h
					stb_textedit.h
					stb_truetype.h )


add_library( imgui ${IMGUI_FILES} )
