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

#  Set C++ 20 Support
set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

#  Give Vscode a fighting chance
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Bring in CMake helpers for TERMINUS projects
include( terminus_cmake )

#  Setup Threading (pthreads for linux)
find_package(Threads REQUIRED)

#  Find dependencies
#set( Boost_USE_MULTITHREADED ON )
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
#ADD_DEFINITIONS(-BOOST_LOG_NO_THREADS)
find_package( Boost REQUIRED )

#  Setup Exports File
configure_file( ${CMAKE_SOURCE_DIR}/templates/Exports.hpp.in
                ${CMAKE_SOURCE_DIR}/include/terminus/log/Exports.hpp )

# Setup Code Coverage
if( TERMINUS_LOG_ENABLE_COVERAGE )
    terminus_coverage_enable()
endif()

terminus_lib_create_header_only()

target_link_libraries( ${PROJECT_NAME} INTERFACE
    Boost::boost
    Boost::json
    Boost::log
    Boost::log_setup
    Boost::system
    Threads::Threads
)

#  Testing
if( TERMINUS_LOG_ENABLE_TESTS)
    enable_testing()
    if( NOT_TERMINUS_LOG_DISABLE_COMPONENT_TESTS)
        add_subdirectory( test/component )
    endif()
    add_subdirectory( test/unit )
endif()

#  Setup Coverage Reporting
if( TERMINUS_LOG_ENABLE_COVERAGE )
    terminus_coverage_create_target()
endif()

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

