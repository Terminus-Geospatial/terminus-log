#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/8/2023
#

#  Configure GoogleTest
message( STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}" )
find_package( GTest REQUIRED )
include( GoogleTest )

set(TEST ${PROJECT_NAME}_test)

add_executable( ${TEST}
    TEST_configure.cpp
    TEST_Logger.cpp
    TEST_Stream_Interceptor.cpp
    TEST_utility.cpp
    TEST_json_formatter.cpp
)

target_link_libraries( ${TEST} PRIVATE
    GTest::gmock_main
    GTest::gtest_main
    ${PROJECT_NAME}
)

gtest_discover_tests( ${TEST} PROPERTIES TIMEOUT 600 )