#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/8/2023

find_package( GTest REQUIRED )
include( GoogleTest )

set(TEST terminus_log_tests)

add_executable( ${TEST}
    TEST_configure.cpp
    TEST_Logger.cpp
    TEST_Stream_Interceptor.cpp
    TEST_utility.cpp
)

target_link_libraries( ${TEST} PRIVATE
    GTest::gmock_main
    GTest::gtest_main
    ${PROJECT_NAME}
)

gtest_discover_tests( ${TEST} )