cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

set( RT_SRC_FILES main.c
            loop.c
            init.c 
            cl_set_arg.c
            event_acts.c
            recognize_scancode.c
            second_camera.c 
            textures.c
            lights.c
            objects.c
            file_reading.c )
PREPEND( RT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/ ${RT_SRC_FILES} )

target_sources( RT PRIVATE ${RT_SRC} )
