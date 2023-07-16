#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/16/2023

include_directories( ../include/terminus/log )

add_library( ${PROJECT_NAME} SHARED
                utility.cpp )

target_include_directories( ${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

terminus_lib_configure( ${PROJECT_NAME} )
