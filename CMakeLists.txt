#**************************** INTELLECTUAL PROPERTY RIGHTS ****************************#
#*                                                                                    *#
#*                           Copyright (c) 2025 Terminus LLC                          *#
#*                                                                                    *#
#*                                All Rights Reserved.                                *#
#*                                                                                    *#
#*          Use of this source code is governed by LICENSE in the repo root.          *#
#*                                                                                    *#
#**************************** INTELLECTUAL PROPERTY RIGHTS ****************************#
#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/8/2023
#
#    Purpose: Build the terminus logging API
#
cmake_minimum_required( VERSION 3.16 FATAL_ERROR )

#  Configure Conan Search Paths
include( "${CMAKE_BINARY_DIR}/conan_toolchain.cmake" )
set( CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE )

# Set the Project-Name
project( ${CONAN_PKG_NAME}
        VERSION ${CONAN_PKG_VERSION}
        HOMEPAGE_URL ${CONAN_PKG_URL}
        DESCRIPTION ${CONAN_PKG_DESCRIPTION}
        LANGUAGES CXX
)

#  Set C++ Info
set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

#  Give Vscode a fighting chance
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Bring in CMake helpers for TERMINUS projects
include( terminus_cmake )

set( CMAKE_COMPILE_WARNING_AS_ERROR ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror" )

#----------------------------------------#
#-          Update Version File         -#
#----------------------------------------#
# Get the current date
string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d %H:%M:%S" )

# Get the current git commit hash
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE TERMINUS_GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file( ${CMAKE_SOURCE_DIR}/templates/exports.hpp.in
                ${CMAKE_BINARY_DIR}/include/terminus/log/exports.hpp )


#--------------------------------#
#-      Find Dependencies       -#
#--------------------------------#
find_package( Boost REQUIRED )

# Setup Code Coverage
if( TERMINUS_LOG_ENABLE_COVERAGE )
    terminus_coverage_enable()
endif()

terminus_lib_create_header_only()

#------------------------------#
#-        Build Library       -#
#------------------------------#
target_link_libraries( ${PROJECT_NAME} INTERFACE
    Boost::json
    Boost::log
    Boost::log_setup
)

#  Testing
if( TERMINUS_LOG_ENABLE_TESTS)
    enable_testing()
    if( NOT_TERMINUS_LOG_DISABLE_COMPONENT_TESTS)
        add_subdirectory( test/component )
    endif()
    add_subdirectory( test/unit )
endif()


#  Install Headers
install( DIRECTORY ${PROJECT_BINARY_DIR}/include/terminus DESTINATION include )
install( DIRECTORY ${PROJECT_SOURCE_DIR}/include/terminus DESTINATION include )

#------------------------------------------------#
#-          Setup CMake Helper Scripts          -#
#------------------------------------------------#
set(INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
configure_file( "cmake/config.cmake.in"
                "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" @ONLY )
write_basic_package_version_file("${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

set( TMNS_LOG_CMAKE_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")
install(
    FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    DESTINATION "${TMNS_LOG_CMAKE_INSTALL_DIR}"
)

install(
    FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    DESTINATION "${TMNS_LOG_CMAKE_INSTALL_DIR}"
)

install(
    EXPORT ${PROJECT_NAME}_exports
    DESTINATION "${TMNS_LOG_CMAKE_INSTALL_DIR}"
    FILE "${PROJECT_NAME}-targets.cmake"
    NAMESPACE "${PROJECT_NAME}::"
)

