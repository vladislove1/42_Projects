cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

set( QUATERNION_FILES
     add_q.c
     chb_q.c
     cmp_q.c
     cos_q.c
     crs_q.c
     dot_q.c
     dst_q.c
     lnr_q.c
     mag_q.c
     nrm_q.c
     opp_q.c
     quaternion.h
     rot_q.c
     scl_q.c
     sqr_q.c
     sub_q.c )
PREPEND( QUATERNION ${CMAKE_CURRENT_SOURCE_DIR}/ ${QUATERNION_FILES} )

target_sources( RT PRIVATE ${QUATERNION} )
target_include_directories( RT PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
