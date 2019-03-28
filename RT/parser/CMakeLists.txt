cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

set (SOURCE_FILES   parser.h
                    parser_private.h
                    parser.c
                    parse_light.c
					parse_obj.c
					parse_vec3.c
					parse_camera.c
					parse_routine.c
					parse_objects_p2.c
					parse_trivial_objects.c )

PREPEND(SOURCES ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCE_FILES})

target_sources( RT PUBLIC ${SOURCES} )
target_include_directories( RT PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
