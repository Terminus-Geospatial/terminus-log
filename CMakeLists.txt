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
set( CMAKE_CXX_STANDARD 20 )
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

add_subdirectory( src )

target_link_libraries( ${PROJECT_NAME} PUBLIC
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
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${INSTALL_CMAKEDIR}
)

install( DIRECTORY include/terminus DESTINATION include )