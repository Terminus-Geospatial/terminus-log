#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/8/2023
#

function( add_component_test SUFFIX FILE )
    set( TEST test_comp_${PROJECT_NAME}_${SUFFIX} )
    add_executable( ${TEST} ${FILE} )
    target_link_libraries( ${TEST} PRIVATE ${PROJECT_NAME} )
endfunction()

add_component_test( global TEST_Global_Logger.cpp )
add_component_test( instance TEST_Instance_Logger.cpp )
add_component_test( boost_settings TEST_Boost_Settings_File.cpp )
add_component_test( boost_location TEST_Boost_Location_Logger.cpp )
add_component_test( boost_json     TEST_Boost_JSON_Logger.cpp )

FILE( COPY logging.conf DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
FILE( COPY logging-location.conf DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
FILE( COPY logging-json.conf DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
