cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

project( RT )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH})

add_definitions( -DCL_SILENCE_DEPRECATION )

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( OpenCL REQUIRED )
find_package( GLEW REQUIRED )
find_package( OPENGL REQUIRED )


FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

macro(GroupSources sources)
 foreach(FILE ${${sources}}) 
     get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

     string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
     string(REPLACE "/" "\\" GROUP "${GROUP}")

     source_group("${GROUP}" FILES "${FILE}")
 endforeach()
endmacro()


include_directories( . )
include_directories( ${FULL_PATH}/includes )

include_directories( ${SDL2_INCLUDE_DIR} )
include_directories( ${SDL2_IMAGE_INCLUDE_DIRS} )
include_directories( ${GLEW_INCLUDE_DIRS} )
include_directories( ${OPENGL_INCLUDE_DIRS} )


add_executable( RT )

add_subdirectory( lib )
add_subdirectory( gui )
add_subdirectory( quaternion )
add_subdirectory( sources )
add_subdirectory( parser )
add_subdirectory( cl )

include_directories( ${LIBRARY_INCLUDE_DIR} )

get_target_property( RT_SOURCES RT SOURCES )
GroupSources( RT_SOURCES )


set( RT_KERNELS kernel.cl )

foreach( LIB_HEADER ${LIBRARY_INCLUDES} )
    source_group( "lib" FILES ${LIB_HEADER} )
endforeach( )

target_sources( RT PRIVATE ${RT_KERNELS} ${LIBRARY_INCLUDES} )

target_link_libraries( RT
                       libft
                       imgui
                       cjson
                       ${SDL2_LIBRARY}
                       ${SDL2_IMAGE_LIBRARIES}
                       ${GLEW_LIBRARIES}
                       ${OPENGL_LIBRARIES}
                       ${OpenCL_LIBRARIES} )
